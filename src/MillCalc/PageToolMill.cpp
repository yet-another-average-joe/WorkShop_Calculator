// PageTool.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PageTool.h"
#include "DataToolDb.h"
#include "PageTCA.h"
#include "Hints.h"

// Boîte de dialogue CPageToolMill

IMPLEMENT_DYNCREATE(CPageToolMill, CPropPageEx)

CPageToolMill::CPageToolMill(UINT nIDTemplate, CData* pData)
	: CPropPageEx(nIDTemplate, pData),
		m_listboxTool(	CLASSES_IDC_EDIT_TOOL,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_EDIT,
						CLASSES_IDC_BUTTON_CANCEL,
						CLASSES_IDC_BUTTON_REC,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_pToolNew=NULL;
	m_pClipboard=NULL;
}

CPageToolMill::CPageToolMill()
	: CPropPageEx(CPageToolMill::IDD, NULL),
		m_listboxTool(	CLASSES_IDC_EDIT_TOOL,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_EDIT,
						CLASSES_IDC_BUTTON_CANCEL,
						CLASSES_IDC_BUTTON_REC,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_pToolNew=NULL;
	m_pClipboard=NULL;
}

CPageToolMill::~CPageToolMill()
{
}

BOOL CPageToolMill::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	CSize size(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	m_btnNew.SetIconMulti(		CLASSES_IDI_ADD,	CLASSES_IDI_ADD_DISABLED, size);
	m_btnDel.SetIconMulti(		CLASSES_IDI_DEL,	CLASSES_IDI_DEL_DISABLED, size);
	m_btnEdit.SetIconMulti(		CLASSES_IDI_EDIT,	CLASSES_IDI_EDIT_DISABLED, size);
	m_btnCancel.SetIconMulti(	CLASSES_IDI_CANCEL,	CLASSES_IDI_CANCEL_DISABLED, size);
	m_btnRec.SetIconMulti(		CLASSES_IDI_REC,	CLASSES_IDI_REC_DISABLED, size);
	m_btnCopy.SetIconMulti(		CLASSES_IDI_COPY,	CLASSES_IDI_COPY_DISABLED, size);
	m_btnPaste.SetIconMulti(	CLASSES_IDI_PASTE,	CLASSES_IDI_PASTE_DISABLED, size);
	m_btnUp.SetIconMulti(		CLASSES_IDI_UP,		CLASSES_IDI_UP_DISABLED, size);
	m_btnDown.SetIconMulti(		CLASSES_IDI_DOWN,	CLASSES_IDI_DOWN_DISABLED, size);

	// positionnement des boutons
	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32
	int x0=0;
	int y0=0;
	UINT nFlags=SWP_NOZORDER | SWP_NOACTIVATE;
	nFlags|=GetEditMode()?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	m_btnNew.SetWindowPos(NULL, x0, y0, cxBtn, cxBtn, nFlags);
	m_btnDel.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnEdit.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnCancel.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnRec.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnCopy.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnPaste.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnUp.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnDown.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);

	ResetPage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageToolMill::ResetPage()
{
	if(!m_fDoneDDE)
		return;

	SetControlsPos();

	SetDlgItemText(CLASSES_IDC_EDIT_TOOL, _T(""));
	CNamedObList* pList= ((CDataToolDb*)m_pData)->Tool_GetList();
	m_listboxTool.SetNamedObList(pList);
	Listbox_Tool_SetCurSel(Data_Tool_GetCurSel());
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	m_btnPaste.EnableWindow(FALSE);
}

void CPageToolMill::UpdatePage(LPARAM lHint /*=0*/)
{
	CPropPageEx::UpdatePage(lHint);

	if(!m_fDoneDDE)
		return;

	switch(lHint)
	{
	case HINT_MODE_EDIT:
		m_btnNew.ShowWindow(TRUE);
		m_btnEdit.ShowWindow(TRUE);
		m_btnRec.ShowWindow(TRUE);
		m_btnDel.ShowWindow(TRUE);
		m_btnUp.ShowWindow(TRUE);
		m_btnDown.ShowWindow(TRUE);
		m_btnCancel.ShowWindow(TRUE);
		m_btnCopy.ShowWindow(TRUE);
		m_btnPaste.ShowWindow(TRUE);

		// forcer le repositionnement des contrôles
		SetControlsPos();
		break;

	case HINT_MODE_READONLY:
		m_btnNew.ShowWindow(FALSE);
		m_btnEdit.ShowWindow(FALSE);
		m_btnRec.ShowWindow(FALSE);
		m_btnDel.ShowWindow(FALSE);
		m_btnUp.ShowWindow(FALSE);
		m_btnDown.ShowWindow(FALSE);
		m_btnCancel.ShowWindow(FALSE);
		m_btnCopy.ShowWindow(FALSE);
		m_btnPaste.ShowWindow(FALSE);

		// forcer le repositionnement des contrôles
		SetControlsPos();
		break;

	case HINT_FILE_CHANGED:
	case HINT_FILE_NEW:
	case HINT_FILE_SAVE:
	case HINT_FILE_SAVEAS:
	case HINT_FILE_SAVECOPYAS:
		ResetPage();
		break;

	case HINT_TOOL_SELCHANGED:
		Listbox_Tool_SetCurSel(Data_Tool_GetCurSel());
		break;

	default:
		break;
	}
}

void CPageToolMill::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_LIST_TOOL, m_listboxTool);
	DDX_Control(pDX, CLASSES_IDC_EDIT_TOOL, m_editTool);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_REC, m_btnRec);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_COPY, m_btnCopy);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_PASTE, m_btnPaste);
}

BEGIN_MESSAGE_MAP(CPageToolMill, CPropPageEx)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_EDIT, &CPageToolMill::OnBnClickedButtonEdit)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DEL, &CPageToolMill::OnBnClickedButtonDel)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_UP, &CPageToolMill::OnBnClickedButtonUp)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DOWN, &CPageToolMill::OnBnClickedButtonDown)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_TOOL, &CPageToolMill::OnEnChangeEditName)
	ON_LBN_SELCHANGE(CLASSES_IDC_LIST_TOOL, &CPageToolMill::OnLbnSelchangeListTool)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_NEW, &CPageToolMill::OnBnClickedButtonNew)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_REC, &CPageToolMill::OnBnClickedButtonRec)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_CANCEL, &CPageToolMill::OnBnClickedButtonCancel)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_COPY, &CPageToolMill::OnBnClickedButtonCopy)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_PASTE, &CPageToolMill::OnBnClickedButtonPaste)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CPageToolMill::OnBnClickedButtonCopy()
{
	if(m_pData!=NULL)
	{
		if(m_pClipboard!=NULL)
			delete m_pClipboard;
		CTool* pTool=Data_Tool_GetCurSel();
		m_pClipboard=new CTool(*pTool);
		m_btnPaste.EnableWindow(TRUE);
	}
}

void CPageToolMill::OnBnClickedButtonPaste()
{
	if(m_pData!=NULL)
	{
		//CTool* pTool=Data_Tool_GetCurSel();
		CTool* pToolNew=new CTool(*m_pClipboard);
		ASSERT(pToolNew!=NULL);
		//*pToolNew=m_clipboard;

		pToolNew->m_strName.Format(_T("Copie de %s"), m_pClipboard->m_strName);
		((CDataToolDb*)m_pData)->Tool_AddTail(pToolNew);

		m_listboxTool.Add(pToolNew);
		Data_Tool_SetCurSel(pToolNew);
		// le document est modifié
		Data_SetModifiedFlag(TRUE);

		Listbox_Tool_SetCurSel(pToolNew);
		delete m_pClipboard;
		m_pClipboard=NULL;
		m_btnPaste.EnableWindow(FALSE);

		UpdateAllOtherPages(HINT_TOOL_ADDED);
	}
}

void CPageToolMill::OnBnClickedButtonNew()
{
	m_listboxTool.OnBnClickedNew();
	m_btnCopy.EnableWindow(FALSE);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);
	m_editTool.SetFocus();
}

void CPageToolMill::OnBnClickedButtonRec()
{
	if(m_listboxTool.IsCreating()) // ajout d'un nouvel élément
	{
		CString strEdit;
		GetDlgItemText(CLASSES_IDC_EDIT_TOOL, strEdit);
		strEdit.Trim();

		ASSERT(m_pToolNew==NULL);

		m_pToolNew = new CTool(strEdit);

		// ajouter un nouveau pCut vide pour chaque matière
		POSITION posCat=Data_Cat_GetHeadPosition();
		while(posCat)
		{
			// objet CCut vide
			CCat* pCat=Data_Cat_GetNext(posCat);
			ASSERT(pCat!=NULL);
			CCut* pEmptyCut=new CCut;
			m_pToolNew->AddCut(pCat->m_nID, pEmptyCut);
		}

		CTool* pTool = (CTool*)m_listboxTool.OnBnClickedRec(m_pToolNew);
		ASSERT(pTool==m_pToolNew);
		m_pToolNew=NULL; // remise à zéro ; l'objet a été ajouté à la liste

		// le document est modifié
		Data_SetModifiedFlag(TRUE);

		Data_Tool_SetCurSel(pTool);

		UpdateAllOtherPages(HINT_TOOL_ADDED);
	}
	else // élément modifié
		if(m_listboxTool.IsEditing())
		{
			CTool* pTool = (CTool*)m_listboxTool.OnBnClickedRec(NULL);
			ASSERT(pTool!=NULL);

			// le document est modifié
			Data_SetModifiedFlag(TRUE);

			Data_Tool_SetCurSel(pTool);
	
			UpdateAllOtherPages(HINT_TOOL_RENAMED);
		}
		else
		{
			ASSERT(0);
		}

	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	m_btnPaste.EnableWindow(FALSE);
}

void CPageToolMill::OnBnClickedButtonEdit()
{
	m_listboxTool.OnBnClickedEdit();
	m_btnCopy.EnableWindow(FALSE);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);
}

void CPageToolMill::OnBnClickedButtonDel()
{
	CTool* pTool=Listbox_Tool_GetCurSel();
	
	if(pTool==NULL)
		return;

	Listbox_Tool_GetCurSel();

	CString str;
	str.Format(CLASSES_IDS_DELETE, pTool->m_strName);

	if(AfxMessageBox(str, MB_YESNO)==IDNO)
		return;
	
	m_listboxTool.OnBnClickedDel();

	int nCurSel=m_listboxTool.GetCurSel();
	pTool=NULL;

	if(nCurSel!=LB_ERR)
		pTool = (CTool*)m_listboxTool.Get(nCurSel);

	// le document est modifié
	Data_SetModifiedFlag(TRUE);

	Data_Tool_SetCurSel(pTool);

	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);

	UpdateAllOtherPages(HINT_CAT_DELETED);
}

void CPageToolMill::OnBnClickedButtonCancel()
{
	m_listboxTool.OnBnClickedCancel();

	// détruire l'objet s'il y a lieu
	if(m_pToolNew!=NULL) // dans ce cas l'opération était "Nouveau"
	{
		delete m_pToolNew;
		m_pToolNew=NULL;
	}
	
	OnLbnSelchangeListTool();
	m_pData->SetModifiedFlag(FALSE);
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);
}

void CPageToolMill::OnBnClickedButtonUp()
{
	m_listboxTool.OnBnClickedUp();
	Data_SetModifiedFlag(TRUE);
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);

	UpdateAllOtherPages(HINT_TOOL_REORDERED);
}

void CPageToolMill::OnBnClickedButtonDown()
{
	m_listboxTool.OnBnClickedDown();
	Data_SetModifiedFlag(TRUE);
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);

	UpdateAllOtherPages(HINT_TOOL_REORDERED);
}

void CPageToolMill::OnLbnSelchangeListTool()
{
	m_listboxTool.OnLbnSelchange();
	Data_Tool_SetCurSel(Listbox_Tool_GetCurSel());

	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	m_btnPaste.EnableWindow(FALSE);
	
	UpdateAllOtherPages(HINT_TOOL_SELCHANGED);
}

void CPageToolMill::OnEnChangeEditName()
{
	// ne prendre en compte que si mode édition
	if(GetEditMode())
		m_listboxTool.OnEditChanged();
}


int CPageToolMill::Listbox_Tool_SetCurSel(CTool* pTool)
{
	int nCount=m_listboxTool.GetCount();
	int n=0;
	while(n<nCount)
	{
		if(pTool==(CTool*)m_listboxTool.GetItemDataPtr(n))
			return m_listboxTool.SetCurSel(n);
		n++;
	}

	return CB_ERR;
}

void CPageToolMill::SetControlsPos()
{
	CPropPageEx::SetControlsPos();

	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32

	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();

	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cyMargin=::GetSystemMetrics(SM_CYEDGE);

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER/*|SWP_NOREDRAW*/;

	if(GetEditMode()==FALSE)
	{
		// dans ce cas la listbox occupe toute la largeur
		int cxMax = cxClient-2*cxMargin;

		m_editTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_editTool.SetWindowPos(NULL, cxMargin, rc.top, cxMax,rc.Height(), uFlags);

		m_listboxTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxTool.SetWindowPos(NULL, cxMargin, rc.top, cxMax, cyClient-rc.top-cxMargin, uFlags);
	}
	else
	{
		m_editTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_editTool.SetWindowPos(NULL, cxBtn, rc.top, cxClient-cxBtn-cxMargin,rc.Height(), uFlags);

		m_listboxTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxTool.SetWindowPos(NULL, cxBtn, rc.top, cxClient-cxBtn-cxMargin, cyClient-rc.top-cyMargin, uFlags);
	}
}

BOOL CPageToolMill::CanChangePage()
{
	if(m_listboxTool.IsEditing() || m_listboxTool.IsCreating())
	{
		MessageBeep(0);
		return FALSE;
	}
	else
		return TRUE;
}


void CPageToolMill::OnDestroy()
{
	CPropPageEx::OnDestroy();

	if(m_pClipboard!=NULL)
		delete m_pClipboard;
}
