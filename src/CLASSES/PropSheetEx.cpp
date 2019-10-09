// PropSheetEx.cpp : fichier d'implémentation
//
// http://www.codeguru.com/cpp/controls/propertysheet/sizing/article.php/c599

#include "stdafx.h"
#include "PropSheetEx.h"
#include "PropPageEx.h"
#include "Data.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"
#include "CEFileFind.h"
#include "DlgSave.h"

// ID standards
#define IDM	128
#define ID_ICON	128

// CPropSheetEx

IMPLEMENT_DYNAMIC(CPropSheetEx, CPropertySheet)

CPropSheetEx::CPropSheetEx(BOOL fHideSHDoneBtn /*=FALSE*/,	// si TRUE, le bouton "ok" est remplacé par "X"
							UINT iSelectPage /*= 0*/,
							CWnd* pParent /*= NULL*/)
	:CPropertySheet(AFX_IDS_APP_TITLE, pParent, iSelectPage)
{
	m_pData=NULL;
	m_fEditMode=FALSE;
	m_fHideSHDoneBtn=fHideSHDoneBtn;
	m_fHideSHDoneBtn=FALSE;	// si TRUE, le bouton "ok" est remplacé par "X"
}

CPropSheetEx::~CPropSheetEx()
{
	delete m_pData;
}

// retourne le dossier des données
void CPropSheetEx::GetDataFolder(CString& strDataFolder)
{
	// récupérer le chemin complet de l'exécutable
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();

	// extraire le dossier
	strDataFolder = strAppDir.Left(strAppDir.ReverseFind('\\'));
}

void CPropSheetEx::DoDataExchange(CDataExchange* pDX)
{
	CPropertySheet::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPropSheetEx, CPropertySheet)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(CLASSES_IDM_MODE_EDIT, &CPropSheetEx::OnModeEdit)
	ON_UPDATE_COMMAND_UI(CLASSES_IDM_MODE_EDIT, &CPropSheetEx::OnUpdateModeEdit)
	ON_WM_PAINT()
	ON_UPDATE_COMMAND_UI(CLASSES_IDM_FILE_SAVE, &CPropSheetEx::OnUpdateIdMenuFileSave)
	ON_UPDATE_COMMAND_UI(CLASSES_IDM_FILE_SAVE_AS, &CPropSheetEx::OnUpdateIdMenuFileSaveAs)
	ON_UPDATE_COMMAND_UI(CLASSES_IDM_FILE_SAVE_COPY_AS, &CPropSheetEx::OnUpdateIdMenuFileSaveCopyAs)
	ON_UPDATE_COMMAND_UI(CLASSES_IDM_FILE_NEW, &CPropSheetEx::OnUpdateIdMenuFileNew)
	ON_COMMAND(CLASSES_IDM_FILE_NEW, &CPropSheetEx::OnIdMenuFileNew)
	ON_COMMAND(CLASSES_IDM_FILE_SAVE, &CPropSheetEx::OnIdMenuFileSave)
	ON_COMMAND(CLASSES_IDM_FILE_SAVE_AS, &CPropSheetEx::OnIdMenuFileSaveAs)
	ON_COMMAND(CLASSES_IDM_FILE_SAVE_COPY_AS, &CPropSheetEx::OnIdMenuFileSaveCopyAs)
END_MESSAGE_MAP()

BOOL CPropSheetEx::OnCommand(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_pData!=NULL);

	// si m_fHideSHDoneBtn==FALSE
	// intercepte le bouton ok pour demander 
	// la sauvegarde du fichier s'il est modifié
	// pour le traitement du bouton "X", c'est impossible
	// envoie un WM_SIZE avec MINIMIZED, et le fait de placer
	// une boîte de dialogue dans OnSize() la remet au 1er plan
	if(LOWORD(wParam)==IDOK)
	{
		if(m_pData->IsModified())
		{
			switch(AfxMessageBox(CLASSES_IDS_SAVE_MODIFIED, 
							MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_DEFBUTTON3))
			{
				case IDCANCEL:	// ne pas quitter
					return TRUE;
				case IDYES:		// enregistrer et quitter
					{
						CString str;
						Data_Save();
						// si aucun nom de fichier n'est donné (IDCANCEL sur la boîte de dialogue DlgSave)
						// ne pas quitter
						if(!m_pData->GetFileName(str))
							return TRUE;
					}
					break;
				case IDNO:		// quitter sans enregistrer
					break;
				default:
					break;
			}
		}
	}

	return CPropertySheet::OnCommand(wParam, lParam);
}

// Gestionnaires de messages de CPropSheetEx
// TCN_SELCHANGING ne prend pas en charge presult qui permet normalement de bloquer
// le changement de sélection
// donc : mémorisation de la page active à chaque changement. S'il y a changement non
// souhaité suite à appel de CPropPageEx::CanChage(), on revient à la page précédente

BOOL CPropSheetEx::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR* pnmh = (LPNMHDR) lParam;

	if (pnmh->code == TCN_SELCHANGING)
		m_nLastActive = GetActiveIndex ();
	else
	if (pnmh->code == TCN_SELCHANGE)
	{
		// get the current page index
		int nCurrentPage = GetActiveIndex();
		// if current page is in our map of disabled pages
		CPropPageEx* pPage = (CPropPageEx*)GetPage(m_nLastActive);
		BOOL fCanChange=pPage->CanChangePage(); // FALSE pour autoriser, TRUE pour interdire (zarbi...)

		if(!fCanChange)
			PostMessage (PSM_SETCURSEL, m_nLastActive);
	}

	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}

// pour support CmdUI (copié collé)
void CPropSheetEx::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
{
	if (bSysMenu)
		return;     // don't support system menu

//#ifndef _WIN32_WCE // OLE
//#ifndef _AFX_NO_OLE_SUPPORT
//	// allow hook to consume message
//	if (m_pNotifyHook != NULL &&
//		m_pNotifyHook->OnInitMenuPopup(pMenu, nIndex, bSysMenu))
//	{
//		return;
//	}
//#endif
//#else
//	(nIndex);
//#endif // !_WIN32_WCE

	ENSURE_VALID(pMenu);
	
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
			// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nItemIndex = 0; nItemIndex < nIndexMax; nItemIndex++)
			{
				if (::GetSubMenu(hParentMenu, nItemIndex) == pMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
///////////////////////////////////////////////////////////////////////////
//	HACK PERSO :	-1 n'est pas affecté aux sous menus sous WinCE ; bug connu
//					conséquence : les popups (sous menus) sont inactifs
//					voir avec Google "OnInitMenuPopup WinCE"
//		if (state.m_nID == (UINT)-1)
		if (state.m_nID >= 0xF000)//== (UINT)-1)
///////////////////////////////////////////////////////////////////////////
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;

///////////////////////////////////////////////////////////////////////////
//	HACK PERSO :	m_bAutoMenuEnable n'est as défini sous WinCE
//
//			state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);
			state.DoUpdate(this, TRUE);
///////////////////////////////////////////////////////////////////////////
		}

		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

// permet l'affichage de la CommandBar
void CPropSheetEx::OnPaint()
{
	CPropertySheet::OnPaint();

	ASSERT(::IsWindow(m_wndCommandBar.GetSafeHwnd()));
	::SetForegroundWindow(m_wndCommandBar.m_hWnd);
}

BOOL CPropSheetEx::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	HICON hIcon=AfxGetApp()->LoadIcon(ID_ICON);
	SetIcon(hIcon, TRUE);			// Définir une grande icône
	SetIcon(hIcon, FALSE);		// Définir une petite icône

	// Remove (hide) the OK button
	//::SHDoneButton(m_hWnd, m_fHideSHDoneBtn==TRUE?SHDB_HIDE:SHDB_SHOW);

	// Create the command bar control
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDM) ||
	    !m_wndCommandBar.AddAdornments(0))
	{
		TRACE0("Impossible de créer CommandBar\n");
		return -1;      // échec de la création
	}

	//m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	// bouton WrkShpCalc actif seulement si le programme est présent
	EnableWrkShpCalcBtn(m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPropSheetEx::OnModeEdit()
{
	m_fEditMode=!m_fEditMode;
	CPropPageEx* pPage=(CPropPageEx*)GetActivePage();
	if(pPage!=NULL)
		pPage->UpdatePage();
}

void CPropSheetEx::OnUpdateModeEdit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pData!=NULL);
	pCmdUI->SetCheck(m_fEditMode);
}

void CPropSheetEx::OnUpdateIdMenuFileNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CPropSheetEx::OnUpdateIdMenuFileSave(CCmdUI *pCmdUI)
{
	ASSERT(m_pData!=NULL);
	pCmdUI->Enable(!m_pData->IsEmpty()&&m_pData->IsModified());
}

void CPropSheetEx::OnUpdateIdMenuFileSaveAs(CCmdUI *pCmdUI)
{
	ASSERT(m_pData!=NULL);
	pCmdUI->Enable(!m_pData->IsEmpty());
}

void CPropSheetEx::OnUpdateIdMenuFileSaveCopyAs(CCmdUI *pCmdUI)
{
	ASSERT(m_pData!=NULL);
	pCmdUI->Enable(!m_pData->IsEmpty());
}

void CPropSheetEx::OnIdMenuFileNew()
{
	ASSERT(m_pData!=NULL);

	if(m_pData->IsModified())
		switch(AfxMessageBox(CLASSES_IDS_SAVE_MODIFIED, 
						MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_DEFBUTTON3))
		{
			case IDCANCEL:
				return;
			case IDYES:
				Data_SaveAs();
				break;
			default:
				break;
		}

	m_pData->DeleteContents();
	m_pData->SetModifiedFlag(FALSE);

	// passer en mode édition
	SetEditMode(TRUE);

	// la page "courante" doit être mise à jour 
	// les autres le sont lors de l'appel à OnSetActive()

	((CPropPageEx*)GetActivePage())->UpdatePage();
}

void CPropSheetEx::OnIdMenuFileSave()
{
	ASSERT(m_pData!=NULL);
	Data_Save();
}

void CPropSheetEx::OnIdMenuFileSaveAs()
{
	ASSERT(m_pData!=NULL);
	Data_SaveAs();
}

void CPropSheetEx::OnIdMenuFileSaveCopyAs()
{
	ASSERT(m_pData!=NULL);
	Data_SaveCopyAs();
}

// lit le fichier ; strFileName = 
BOOL CPropSheetEx::Data_FileRead(const CString& strFilePath)
{
	ASSERT(m_pData!=NULL);

	// si le fichier courant a été modifié, proposer de l'enregistrer
	if(m_pData->IsModified())
		switch(AfxMessageBox(CLASSES_IDS_SAVE_MODIFIED, 
						MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_DEFBUTTON3))
		{
			case IDCANCEL:
				return TRUE;
			case IDYES:
				Data_Save();
				break;
			default:
				break;
		}

	// lire le fichier
	return m_pData->FileRead(strFilePath);
}

void CPropSheetEx::Data_Save()
{
	ASSERT(m_pData!=NULL);

	m_pData->FileWrite();
	m_pData->SetModifiedFlag(FALSE);
}

void CPropSheetEx::Data_SaveAs()
{
	ASSERT(m_pData!=NULL);

	CDlgSave dlgSave;
	dlgSave.m_nIDTitle=CLASSES_IDS_SAVE_AS;
	CString strFileName;
	m_pData->GetFileName(strFileName);
	dlgSave.m_strFileName=strFileName;
	CString strFileExt;
	GetDataFileExt(strFileExt);
	dlgSave.m_strFileExt=strFileExt;
	if(dlgSave.DoModal()==IDOK)
	{
		// si le fichier existe déjà
		if(Data_FileExist(dlgSave.m_strFileName))
		{
			if(AfxMessageBox(CLASSES_IDS_PROMPT_OVERWRITE, 
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2)==IDNO)
				return;
		}

		// récupérer le chemin complet de l'exécutable
		CString strAppDir;
		::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
		strAppDir.ReleaseBuffer();

		// extraire le dossier
		strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));

		CString strFilePath=strAppDir+_T("\\")+dlgSave.m_strFileName+_T(".")+strFileExt;

		if(m_pData->FileWrite(strFilePath))
		{
			m_pData->SetFilePath(strFilePath);
			m_pData->SetModifiedFlag(FALSE);
			CPropPageEx* pPage=(CPropPageEx*)GetActivePage();
			pPage->UpdatePage();
		}
	}
}

void CPropSheetEx::Data_SaveCopyAs()
{
	ASSERT(m_pData!=NULL);

	CDlgSave dlgSave;
	dlgSave.m_nIDTitle=CLASSES_IDS_SAVE_AS;
	CString strFileName;
	m_pData->GetFileName(strFileName);
	dlgSave.m_strFileName=strFileName;
	CString strFileExt;
	GetDataFileExt(strFileExt);
	dlgSave.m_strFileExt=strFileExt;
	if(dlgSave.DoModal()==IDOK)
	{
		// si le fichier existe déjà
		if(Data_FileExist(dlgSave.m_strFileName))
		{
			if(AfxMessageBox(CLASSES_IDS_PROMPT_OVERWRITE, 
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2)==IDNO)
				return;
		}

		// récupérer le chemin complet de l'exécutable
		CString strAppDir;
		::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
		strAppDir.ReleaseBuffer();

		// extraire le dossier
		strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));

		CString strFilePath=strAppDir+_T("\\")+dlgSave.m_strFileName+_T(".")+strFileExt;

		if(m_pData->FileWrite(strFilePath))
		{
			//m_pData->SetFilePath(strFilePath);
			//m_pData->SetModifiedFlag(FALSE);
			CPropPageEx* pPage=(CPropPageEx*)GetActivePage();
			pPage->UpdatePage();
		}
	}
}

BOOL CPropSheetEx::Data_FileExist(const CString& strFileName)
{
	ASSERT(m_pData!=NULL);

	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFileExt;
	GetDataFileExt(strFileExt);
	CString strFind = strAppDir + _T("\\") + strFileName + _T(".") + strFileExt;
	CString strFileNameExt=strFileName + _T(".") + strFileExt;

	CFileFind ff;

	if (!ff.FindFile(strFind)) 
		return FALSE;
	
	BOOL bNext;

	do 
	{
		bNext=ff.FindNextFile();
		CString str=ff.GetFileName();
		if(strFileNameExt == str)
			return TRUE;
	} while (bNext);

	return FALSE;
}

