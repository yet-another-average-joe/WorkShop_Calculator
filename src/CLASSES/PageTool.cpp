// PageTool.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PageTool.h"
#include "DataToolDb.h"
#include "PageTCA.h"
#include "CLASSES.h"

// Boîte de dialogue CPageTool

IMPLEMENT_DYNCREATE(CPageTool, CPropPageEx)

void CPageTool::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_LIST_TOOL, m_listboxTool);
	DDX_Control(pDX, CLASSES_IDC_EDIT_TOOL, m_editTool);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_COPY, m_btnCopy);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_PASTE, m_btnPaste);
	DDX_Control(pDX, CLASSES_IDC_EDIT_AP, m_editAp);
	DDX_Control(pDX, CLASSES_IDC_EDIT_AE, m_editAe);
	DDX_Control(pDX, CLASSES_IDC_STATIC_AP, m_staticAp);
	DDX_Control(pDX, CLASSES_IDC_STATIC_AE, m_staticAe);
	DDX_Control(pDX, CLASSES_IDC_STATIC_XD1, m_staticXd1);
	DDX_Control(pDX, CLASSES_IDC_STATIC_XD2, m_staticXd2);
}

BEGIN_MESSAGE_MAP(CPageTool, CPropPageEx)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DEL, &CPageTool::OnBnClickedButtonDel)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_UP, &CPageTool::OnBnClickedButtonUp)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DOWN, &CPageTool::OnBnClickedButtonDown)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_TOOL, &CPageTool::OnEnChangeEditName)
	ON_LBN_SELCHANGE(CLASSES_IDC_LIST_TOOL, &CPageTool::OnLbnSelchangeListTool)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_NEW, &CPageTool::OnBnClickedButtonNew)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_COPY, &CPageTool::OnBnClickedButtonCopy)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_PASTE, &CPageTool::OnBnClickedButtonPaste)
	ON_WM_DESTROY()
	ON_EN_CHANGE(CLASSES_IDC_EDIT_AP, &CPageTool::OnEnChangeIdcEditAp)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_AE, &CPageTool::OnEnChangeIdcEditAe)
	// message envoyé par la listbox quadn réorganisée par drag and drop
	ON_MESSAGE(WMU_LBUPDOWN_DRAGGED, OnDragAndDrop)
END_MESSAGE_MAP()

CPageTool::CPageTool(CData* pData, BOOL fMillTool/*=FALSE*/)
	: CPropPageEx(CPageTool::IDD, pData),
	m_fMillTool(fMillTool),
		m_listboxTool(	CLASSES_IDC_EDIT_TOOL,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_editAp.m_bNoGray=TRUE;
	m_editAe.m_bNoGray=TRUE;

	m_pClipboard=NULL;
	m_fPosSaved=FALSE;
}

CPageTool::CPageTool(BOOL fMillTool/*=FALSE*/)
	: CPropPageEx(CPageTool::IDD, NULL),
	m_fMillTool(fMillTool),
		m_listboxTool(	CLASSES_IDC_EDIT_TOOL,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_editAp.m_bNoGray=TRUE;
	m_editAe.m_bNoGray=TRUE;

	m_pClipboard=NULL;
	m_fPosSaved=FALSE;
}

CPageTool::~CPageTool()
{
}

BOOL CPageTool::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	InitializeButtons();
	SetControlsPos();

	m_listboxTool.EnableDragAndDrop(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageTool::ResetPage()
{
	if(!m_fDoneDDE)
		return;

	CNamedObList* pList= Data_Tool_GetList();
	ASSERT_VALID(pList);
	m_listboxTool.SetNamedObList(pList);
	CTool* pTool=Data_Tool_GetCurSel();
	
	if(pTool==NULL) // base de données vide
		return;

	ASSERT_VALID(pTool);
	Listbox_Tool_SetCurSel(pTool);

	OnLbnSelchangeListTool();

	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);
	m_btnPaste.EnableWindow(FALSE);

	if(m_fMillTool)
	{
		CTool* pTool=Data_Tool_GetCurSel();
		if(pTool!=NULL)
		{
				if(pTool->m_ap!=0)
					SetAp(pTool->m_ap);
				else
					ClearAp();

				if(pTool->m_ae!=0)
					SetAe(pTool->m_ap);
				else
					ClearAe();
		}
		else
		{
			ClearAp();
			ClearAe();
		}
	}
}

void CPageTool::OnBnClickedButtonCopy()
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

void CPageTool::OnBnClickedButtonPaste()
{
	if(m_pData!=NULL)
	{
		CTool* pToolNew=new CTool(*m_pClipboard);
		ASSERT(pToolNew!=NULL);

		pToolNew->m_strName.Format(_T("Copie de %s"), m_pClipboard->m_strName);
		((CDataToolDb*)m_pData)->Tool_AddTail(pToolNew);

		m_listboxTool.Listbox_Add(pToolNew);
		Data_Tool_SetCurSel(pToolNew);
		// le document est modifié
		Data_SetModifiedFlag(TRUE);

		Listbox_Tool_SetCurSel(pToolNew);
		delete m_pClipboard;
		m_pClipboard=NULL;
		m_btnPaste.EnableWindow(FALSE);
	}
}

void CPageTool::OnBnClickedButtonNew()
{
	// créer un nouvel outil
	CString str=_T("<nouvel outil>");
	CTool* pToolNew = new CTool(str);	

	// ajouter un nouveau pCut vide pour chaque matière
	POSITION posCat=Data_Cat_GetHeadPosition();
	while(posCat)
	{
		// objet CCut vide
		CCat* pCat=Data_Cat_GetNext(posCat);
		ASSERT(pCat!=NULL);
		CCut* pEmptyCut=new CCut;
		pToolNew->AddCut(pCat->m_nID, pEmptyCut);
	}

	CTool* pTool = (CTool*)m_listboxTool.OnBnClickedAdd(pToolNew);
	ASSERT(pTool==pToolNew);

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Tool_SetCurSel(pTool);
}


void CPageTool::OnBnClickedButtonDel()
{
	m_listboxTool.OnBnClickedDel();

	int nCurSel=m_listboxTool.GetCurSel();
	CTool* pTool=NULL;

	if(nCurSel!=LB_ERR)
		pTool = (CTool*)m_listboxTool.Listbox_Get(nCurSel);

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Tool_SetCurSel(pTool);

	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);

	if(m_pClipboard!=NULL)
		delete m_pClipboard;
	
	m_btnPaste.EnableWindow(FALSE);
}

void CPageTool::OnBnClickedButtonUp()
{
	m_listboxTool.OnBnClickedUp();
	Data_SetModifiedFlag(TRUE);
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);

	if(m_pClipboard!=NULL)
		delete m_pClipboard;

	m_btnPaste.EnableWindow(FALSE);
}

void CPageTool::OnBnClickedButtonDown()
{
	m_listboxTool.OnBnClickedDown();
	Data_SetModifiedFlag(TRUE);
	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);

	if(m_pClipboard!=NULL)
		delete m_pClipboard;

	m_btnPaste.EnableWindow(FALSE);
}

void CPageTool::OnLbnSelchangeListTool()
{
	m_listboxTool.OnLbnSelchange();
	CTool* pTool=Listbox_Tool_GetCurSel();
	ASSERT_VALID(pTool);
	Data_Tool_SetCurSel(pTool);

	if(m_fMillTool)
	{
		CTool* pTool=Data_Tool_GetCurSel();
		if(pTool!=NULL)
		{
			ASSERT_VALID(pTool);

			if(pTool->m_ap!=0)
				SetAp(pTool->m_ap);
			else
				ClearAp();

			if(pTool->m_ae!=0)
				SetAe(pTool->m_ae);
			else
				ClearAe();
		}
		else
		{
			ClearAp();
			ClearAe();
		}
	}

	//if(GetEditMode())
	//{
	//	m_btnCopy.EnableWindow(m_listboxTool.GetCurSel()!=LB_ERR);

	//	//if(m_pClipboard!=NULL)
	//	//{
	//	//	ASSERT_VALID(m_pClipboard);
	//	//	delete m_pClipboard;
	//	//}

	//	//m_btnPaste.EnableWindow(FALSE);
	//}
}

void CPageTool::OnEnChangeEditName()
{
	// ne prendre en compte que si mode édition
	if(GetEditMode())
	{
		// récupérer le texte de l'edit
		CString str;
		GetDlgItemText(CLASSES_IDC_EDIT_TOOL, str);
		CTool* pTool=Data_Tool_GetCurSel();

		if(pTool==NULL) // base de données vide
			return;

		ASSERT_VALID(pTool);

		if(pTool->m_strName==str)
			return;
		
		// modifier le texte dans la listbox
		int nCurSel=m_listboxTool.GetCurSel();
		
		if(nCurSel==LB_ERR)
		{
			//ASSERT(0);
			return;
		}
		
		pTool=(CTool*)m_listboxTool.GetItemDataPtr(nCurSel);
		ASSERT_VALID(pTool);
		pTool->m_strName=str;
		m_listboxTool.DeleteString(nCurSel);
		m_listboxTool.InsertString(nCurSel, str);
		m_listboxTool.SetItemDataPtr(nCurSel, pTool);
		m_listboxTool.SetCurSel(nCurSel);

		Data_SetModifiedFlag(TRUE);
	}
}


int CPageTool::Listbox_Tool_SetCurSel(CTool* pTool)
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

void CPageTool::InitializeButtons()
{
	CRect rc;
	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32

	// initialisation des boutons
	CSize size(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	m_btnNew.SetIconMulti(		CLASSES_IDI_ADD,	CLASSES_IDI_ADD_DISABLED, size);
	m_btnDel.SetIconMulti(		CLASSES_IDI_DEL,	CLASSES_IDI_DEL_DISABLED, size);
	m_btnCopy.SetIconMulti(		CLASSES_IDI_COPY,	CLASSES_IDI_COPY_DISABLED, size);
	m_btnPaste.SetIconMulti(	CLASSES_IDI_PASTE,	CLASSES_IDI_PASTE_DISABLED, size);
	m_btnUp.SetIconMulti(		CLASSES_IDI_UP,		CLASSES_IDI_UP_DISABLED, size);
	m_btnDown.SetIconMulti(		CLASSES_IDI_DOWN,	CLASSES_IDI_DOWN_DISABLED, size);
	
	// positionnement des boutons ; les positions ne cahngent jamais
	int x0=0;
	int y0=0;
	UINT nFlags=SWP_NOZORDER | SWP_NOACTIVATE;
	nFlags|=GetEditMode()?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	m_btnNew.SetWindowPos(NULL, x0, y0, cxBtn, cxBtn, nFlags);
	m_btnDel.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnCopy.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnPaste.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnUp.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnDown.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
}

void CPageTool::SetControlsPos()
{
	CPropPageEx::SetControlsPos();

	// sauvegarder les positions "resource" avant appel 
	// car appel à SetControlsPos
	if(!m_fPosSaved)
	{
		CRect rc;
		m_editTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_yEditTool=rc.top;

		m_editAp.GetWindowRect(rc);
		ScreenToClient(rc);
		m_yEditAp=rc.top;

		m_listboxTool.GetWindowRect(rc);
		ScreenToClient(rc);
		m_yListTool=rc.top;

		m_fPosSaved=TRUE;
	}

	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32

	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();

	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cyMargin=::GetSystemMetrics(SM_CYEDGE);

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	CRect rcClient;
	GetClientRect(rcClient);
	m_editTool.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editTool.SetWindowPos(NULL, cxBtn, m_yEditTool, rcClient.Width()-cxBtn-cxMargin, rc.Height(), SWP_NOZORDER|SWP_NOOWNERZORDER);

	if(!m_fMillTool)
	{	
		if(!GetEditMode())
		{
			// reposiitonner la liste pour recouvrir l'edit
			m_listboxTool.SetWindowPos(NULL, cxMargin, m_yEditTool, cxClient-2*cxMargin, cyClient-cyMargin-m_yEditTool, uFlags);
		}
		else
		{
			// si mode édition, découvrir l'edit, recouvrir ap ae
			m_listboxTool.SetWindowPos(NULL, cxBtn, m_yEditAp, cxClient-cxMargin-cxBtn, cyClient-cyMargin-m_yEditAp, uFlags);
		}
	}
	else
	{
		if(!GetEditMode())
		{
			// remonter ap et ae au niveau de l'edit
			m_staticAp.GetWindowRect(rc);
			ScreenToClient(rc);
			m_staticAp.SetWindowPos(NULL, rc.left, m_yEditTool+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_editAp.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editAp.SetWindowPos(NULL, rc.left, m_yEditTool, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_staticXd1.GetWindowRect(rc);
			ClientToScreen(rc);
			m_staticXd1.SetWindowPos(NULL, rc.left, m_yEditTool+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

			m_staticAe.GetWindowRect(rc);
			ScreenToClient(rc);
			m_staticAe.SetWindowPos(NULL, rc.left, m_yEditTool+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_editAe.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editAe.SetWindowPos(NULL, rc.left, m_yEditTool, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_staticXd2.GetWindowRect(rc);
			ClientToScreen(rc);
			m_staticXd2.SetWindowPos(NULL, rc.left, m_yEditTool+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

			// positionner la listbox
			m_listboxTool.GetWindowRect(rc);
			ScreenToClient(rc);
			m_listboxTool.SetWindowPos(NULL, cxMargin, m_yEditAp, cxClient-2*cxMargin, cyClient-cyMargin-m_yEditAp, uFlags);
		}
		else
		{
			// ramener ap et ae à leur position d'origine
			m_staticAp.GetWindowRect(rc);
			ScreenToClient(rc);
			m_staticAp.SetWindowPos(NULL, rc.left, m_yEditAp+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_editAp.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editAp.SetWindowPos(NULL, rc.left, m_yEditAp, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_staticXd1.GetWindowRect(rc);
			ClientToScreen(rc);
			m_staticXd1.SetWindowPos(NULL, rc.left, m_yEditAp+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

			m_staticAe.GetWindowRect(rc);
			ScreenToClient(rc);
			m_staticAe.SetWindowPos(NULL, rc.left, m_yEditAp+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_editAe.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editAe.SetWindowPos(NULL, rc.left, m_yEditAp, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);
			m_staticXd2.GetWindowRect(rc);
			ClientToScreen(rc);
			m_staticXd2.SetWindowPos(NULL, rc.left, m_yEditAp+cyMargin, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

			// positionner la listbox
			m_listboxTool.SetWindowPos(NULL, cxBtn, m_yListTool, cxClient-cxBtn-cxMargin, cyClient-cyMargin-m_yListTool, uFlags);
		}
	}
}

BOOL CPageTool::CanChangePage()
{
	return TRUE;
}


void CPageTool::OnDestroy()
{
	CPropPageEx::OnDestroy();

	if(m_pClipboard!=NULL)
		delete m_pClipboard;
}

void CPageTool::OnEnChangeIdcEditAp()
{
	TRACE(_T("CPageTool::OnEnChangeIdcEditAp()\n"));
	if(!GetEditMode())
		return;

	if(m_fMillTool)
	{
		CTool* pTool=Data_Tool_GetCurSel();
		if(pTool!=NULL)
		{
			int ap=GetDlgItemInt(CLASSES_IDC_EDIT_AP);
			if(ap!=pTool->m_ap)
			{
				pTool->m_ap=GetDlgItemInt(CLASSES_IDC_EDIT_AP);
				m_pData->SetModifiedFlag(TRUE);
			}
		}
	}
}

void CPageTool::OnEnChangeIdcEditAe()
{
	TRACE(_T("CPageTool::OnEnChangeIdcEditAe()\n"));
	if(!GetEditMode())
		return;

	if(m_fMillTool)
	{
		CTool* pTool=Data_Tool_GetCurSel();
		if(pTool!=NULL)
		{
			int ae=GetDlgItemInt(CLASSES_IDC_EDIT_AE);
			if(ae!=pTool->m_ae)
			{
				pTool->m_ae=GetDlgItemInt(CLASSES_IDC_EDIT_AE);
				m_pData->SetModifiedFlag(TRUE);
			}
		}
	}
}

LRESULT CPageTool::OnDragAndDrop(WPARAM, LPARAM)
{
	Data_SetModifiedFlag(TRUE);
	return 0;
}

void CPageTool::UpdateControlsStyles()
{
	if(GetEditMode())
	{
		m_btnNew.ShowWindow(SW_SHOW);
		m_btnNew.EnableWindow(TRUE);
		m_btnDel.ShowWindow(SW_SHOW);
		m_btnUp.ShowWindow(SW_SHOW);
		m_btnDown.ShowWindow(SW_SHOW);
		m_btnCopy.ShowWindow(SW_SHOW);
		m_btnPaste.ShowWindow(SW_SHOW);
		m_editTool.ShowWindow(SW_SHOW);
		m_listboxTool.EnableDragAndDrop(TRUE);
		if(m_fMillTool)
		{
			m_editAp.EnableWindow(TRUE);
			m_editAe.EnableWindow(TRUE);
			m_editAp.SetReadOnly(FALSE);
			m_editAe.SetReadOnly(FALSE);
		}

		// forcer le repositionnement des contrôles
		SetControlsPos();
	}
	else
	{
		m_btnNew.ShowWindow(SW_HIDE);
		m_btnDel.ShowWindow(SW_HIDE);
		m_btnUp.ShowWindow(SW_HIDE);
		m_btnDown.ShowWindow(SW_HIDE);
		m_btnCopy.ShowWindow(SW_HIDE);
		m_btnPaste.ShowWindow(SW_HIDE);
		m_editTool.ShowWindow(SW_HIDE);
		m_listboxTool.EnableDragAndDrop(FALSE);

		if(m_fMillTool)
		{
			m_editAp.EnableWindow(FALSE);
			m_editAe.EnableWindow(FALSE);
			m_editAp.SetReadOnly(TRUE);
			m_editAe.SetReadOnly(TRUE);
		}

		// forcer le repositionnement des contrôles
		SetControlsPos();
	}
}

void CPageTool::OnChangeEditMode()
{
	UpdateControlsStyles();
}

BOOL CPageTool::OnSetActive()
{
	// metttre à jour la liste
	ResetPage();

	return CPropPageEx::OnSetActive();
}