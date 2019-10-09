// ListBoxUpDown.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ListBoxUpDown2.h"
#include "CLASSES_rc.h"
// CListboxUpDown3

// timers
#define TID_SCROLLDOWN  100
#define TID_SCROLLUP    101


IMPLEMENT_DYNAMIC(CListboxUpDown3, CListBox)

CListboxUpDown3::CListboxUpDown3(	int nIdEdit,			// EDIT associé
									int nIdButtonNew,		// BUTTON nouveau
									int nIdButtonDel,		// BUTTON supprimer
									int nIdButtonUp,		// BUTTON monter 
									int nIdButtonDown)		// BUTTON descendre
{
	m_nIdEdit=nIdEdit;
	m_nIdButtonDel=nIdButtonDel;
	m_nIdButtonUp=nIdButtonUp;
	m_nIdButtonDown=nIdButtonDown;
	m_nIdButtonNew=nIdButtonNew;

	m_nMovingIndex=-1;
	m_nMoveToIndex=-1;
	m_fCaptured=FALSE;
	m_dwInterval=0;
	m_fDrag=FALSE;
	m_bEnableDragAndDrop=FALSE;
}

void CListboxUpDown3::SetNamedObList(CNamedObList* pNamedObList)
{
	ResetContent();
	m_pNamedObList=pNamedObList;

	if(pNamedObList==NULL)
	{
		UpdateCmdUI();
		SetEditText(NULL);
		return;
	}

	ASSERT_VALID(pNamedObList);
	POSITION pos = m_pNamedObList->GetHeadPosition();

	if(!pos)
	{
		UpdateCmdUI();
		SetEditText(NULL);
		return;
	}

	while(pos)
		Listbox_Add(m_pNamedObList->GetNext(pos));

	int n=GetCount();
	VERIFY(SetCurSel(0)!=LB_ERR);
	UpdateCmdUI();
}

CListboxUpDown3::~CListboxUpDown3()
{
}


BEGIN_MESSAGE_MAP(CListboxUpDown3, CListBox)
//	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Gestionnaires de messages de CListboxUpDown3

void CListboxUpDown3::OnBnClickedDel()
{
	int nSel=GetCurSel();
	ASSERT(nSel!=LB_ERR);
	CObjNamed* pOb=Listbox_Get(nSel);
	ASSERT_VALID(pOb);

	CString str;
	str.Format(CLASSES_IDS_DELETE, pOb->m_strName);

	if(AfxMessageBox(str, MB_YESNO)==IDNO)
		return;

	CObjNamed* pRmv=Listbox_Remove(nSel); // l'objet associé sera détruit
	ASSERT(pRmv==pOb);
	ASSERT_VALID(pRmv);
	POSITION pos=m_pNamedObList->Find(pRmv);
	ASSERT(pos!=NULL);
	m_pNamedObList->RemoveAt(pos);
	delete pRmv;

	// mettre à jour l'edit
	int nCurSel=GetCurSel();
	if(nCurSel!=LB_ERR)
	{
		CObjNamed* pOb=Listbox_Get(nCurSel);
		ASSERT_VALID(pOb);
		SetEditText(pOb->m_strName);
	}
	else
	{
		SetEditText(NULL);
	}

	UpdateCmdUI();
}

int CListboxUpDown3::Listbox_Add(CObjNamed* pData)
{
	ASSERT_VALID(pData);
	int nIndex = AddString(pData->m_strName);
	ASSERT(nIndex!=LB_ERRSPACE);
	ASSERT(nIndex!=LB_ERR);
	
	VERIFY(SetItemDataPtr(nIndex, pData)!=LB_ERR);

	return nIndex;
}

CObjNamed* CListboxUpDown3::OnBnClickedAdd(CObjNamed* pDataNew)
{
	ASSERT_VALID(pDataNew);
	CString strEdit;
/*	
BUG : SI LISTE VIDE ET EDIT VIDE, IMPOSSIBLE DE CREER UN OUTIL !!!
	if(!GetParent()->GetDlgItemText(m_nIdEdit, strEdit)) // chaine vide
	{
		UpdateCmdUI();
		return NULL;
	}
*/
	int nItem = Listbox_Add(pDataNew);
	
	ASSERT(nItem!=LB_ERR);
	int nCount=GetCount();

	if(nCount==LB_ERR) // liste vide
	{
		UpdateCmdUI();
		return NULL;
	}

	int nRet=_SetCurSel(nItem);
	ASSERT(nRet!=LB_ERR);

	ASSERT_VALID(m_pNamedObList);
	m_pNamedObList->AddTail(pDataNew);


	CEdit* pEdit=GetEdit();
	pEdit->EnableWindow(TRUE);
	pEdit->SetFocus();
	pEdit->SetSel(0, -1);


	UpdateCmdUI();

	return Listbox_Get(nRet);
}

void CListboxUpDown3::OnLbnSelchange()
{
	EnableEdit(FALSE);

	int nCurSel=GetCurSel();

	if(nCurSel==LB_ERR)
	{
		SetEditText(NULL);
		return;
	}

//	SetRedraw(FALSE);
	CObjNamed* pOb=(CObjNamed*)Listbox_Get(nCurSel);
	ASSERT_VALID(pOb);
	SetEditText(pOb->m_strName);
	UpdateCmdUI();
//	SetRedraw(TRUE);
//	Invalidate();
//	UpdateWindow();
}

CObjNamed* CListboxUpDown3::Listbox_Remove(int nIndex)
{
	ASSERT(nIndex!=LB_ERR);
	CObjNamed* pObj=Listbox_Get(nIndex);
	ASSERT_VALID(pObj);
	ASSERT(nIndex>=0 && nIndex<GetCount());

	int nCount=GetCount();

	if(nCount <=0 || DeleteString(nIndex)==LB_ERR )
		return (CObjNamed*)LB_ERR;

	nCount=GetCount(); // count a été diminué de 1
	SetCurSel(max(-1,min(nIndex, nCount-1)));

	return pObj;
}

//int CListboxUpDown3::Listbox_Insert(int nIndex, CObjNamed* pData)
//{
//	ASSERT(nIndex>LB_ERR);
//	ASSERT_VALID(pData);
//	int nResult=InsertString(nIndex, pData->m_strName);
//
//	if(nResult!=LB_ERR)
//	{
//		VERIFY(nResult==SetItemDataPtr(nResult, pData));
//	}
//
//	return nResult;
//}

//int CListboxUpDown3::Set(int nIndex, CObjNamed* pData)
//{
//	ASSERT(pData!=NULL);
//	int nCurSel = GetCurSel();
//	if(nCurSel==LB_ERR)
//		return LB_ERR;
//	if(pData->m_strName.GetLength()>0)
//	{
//		if(Insert(nCurSel, pData)==LB_ERR)
//			return LB_ERR;
//		// ne pas détruire l'objet associé ! (transféré)
//		if((int)Remove(nCurSel+1)==LB_ERR)
//			return LB_ERR; 
//		if(_SetCurSel(nCurSel)==LB_ERR)
//			return LB_ERR;
//	}
//	return nIndex;
//}
//
//int CListboxUpDown3::Set(int nIndex, CString& strTitle)
//{
//	CObjNamed* pData = Get(nIndex);
//	ASSERT(pData!=NULL);
//	pData->m_strName=strTitle;
//
//	return Set(nIndex, pData);
//}

CObjNamed* CListboxUpDown3::Listbox_MoveCurSelUp()
{
	int nCurSel = GetCurSel();
	
	if(nCurSel==LB_ERR)
		return NULL;

	if(nCurSel==0)
		return NULL;

	// sauvegarder les infos
	CObjNamed* pData = Listbox_Get(nCurSel);
	ASSERT(pData!=NULL);

	CString str;
	GetText(nCurSel, str);

	int iItemNew=InsertString(nCurSel-1, str);
	if(iItemNew==LB_ERR)
		return NULL;

	if(SetItemDataPtr(iItemNew, pData)==LB_ERR)
		return NULL;

	// ne pas détruire l'objet, référencé par l'item nouvellement ajouté
	if((int)Listbox_Remove(iItemNew+2)==LB_ERR) // envoie  EN_CHANGE
		return NULL; 

	if(SetCurSel(iItemNew)==LB_ERR)
		return NULL;

	SetEditText(str);

	return Listbox_Get(iItemNew);
}

CObjNamed* CListboxUpDown3::Listbox_MoveCurSelDown()
{
	int nCurSel = GetCurSel();

	if(nCurSel==LB_ERR)
		return NULL;

	if(nCurSel==GetCount()-1)
		return NULL;

	// sauvegarder les infos
	CObjNamed* pData = Listbox_Get(nCurSel);
	ASSERT(pData!=NULL);

	CString str;
	GetText(nCurSel, str);

	int iItemNew=InsertString(nCurSel+2, str);
	if(iItemNew==LB_ERR)
		return NULL;

	if(SetItemDataPtr(iItemNew, pData)==LB_ERR)
		return NULL;

	// ne pas détruire l'objet, référencé par l'item nouvellement ajouté
	if((int)Listbox_Remove(iItemNew-2)==LB_ERR)
		return NULL; 

	if(SetCurSel(iItemNew-1)==LB_ERR)
		return NULL;
	
	SetEditText(str);

	return Listbox_Get(iItemNew-1);
}

CObjNamed* CListboxUpDown3::OnBnClickedUp()
{
	SetRedraw(FALSE);
	CObjNamed* pOb = Listbox_MoveCurSelUp();
	ASSERT(pOb!=NULL);

	// déplacer l'objet dans la liste au dessus du précédent
	POSITION pos=m_pNamedObList->Find(pOb);
	m_pNamedObList->GetPrev(pos);
	m_pNamedObList->InsertBefore(pos, pOb);
	m_pNamedObList->GetNext(pos);
	m_pNamedObList->RemoveAt(pos);
	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();

	UpdateCmdUI();
	return pOb;
}

CObjNamed* CListboxUpDown3::OnBnClickedDown()
{
	SetRedraw(FALSE);
	CObjNamed* pOb = Listbox_MoveCurSelDown();
	ASSERT(pOb!=NULL);

	// déplacer l'objet dans la liste en dessous du suivant
	POSITION pos=m_pNamedObList->Find(pOb);
	m_pNamedObList->GetNext(pos);
	m_pNamedObList->InsertAfter(pos, pOb);
	m_pNamedObList->GetPrev(pos);
	m_pNamedObList->RemoveAt(pos);
	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();

	UpdateCmdUI();
	return pOb;
}

int CListboxUpDown3::_SetCurSel(int nSelect)
{
	ASSERT(nSelect>=0 || nSelect<GetCount());

	int nRet = SetCurSel(nSelect);
	ASSERT(nRet==nSelect);

	if(nRet!=LB_ERR)
	{
		CObjNamed* pOb=Listbox_Get(nSelect);
		ASSERT(pOb!=NULL);
		ASSERT((int)pOb!=LB_ERR);
		SetEditText(pOb->m_strName);
	}
	else
	{
		SetEditText(NULL);
	}

	return nRet;
}

int CListboxUpDown3::_SetCurSel(CObjNamed* pObjSel)
{
	if(pObjSel==NULL)
	{
		return _SetCurSel(-1);
	}

	int nSel=-1;
	int nCount=GetCount();

	for(int i=0; i<nCount; i++)
	{
		CObjNamed* pOb=Listbox_Get(i);
		if(pOb==pObjSel)
		{
			nSel=i;
			break;
		}
	}
	return _SetCurSel(nSel);
}

void CListboxUpDown3::UpdateCmdUI()
{
	int nCount = GetCount();
	int nCurSel = GetCurSel();

	// désactiver la listbox si vide
	if(nCount<0)
	{
		EnableWindow(FALSE);
	}
	else
	{
		EnableWindow(TRUE);
	}

	// passer l'edit en read only si liste vide ou aucune sélection
	if(nCount<0 || nCurSel<0)
	{
		EnableEdit(FALSE);
	}
	else
	{
		EnableEdit(TRUE);
	}

	// gestion du bouton "Supprimer"

/////////////////////////////////////////////////////////////////////
	if(nCount<=0 /*|| // problèmes avec 0, 1 et 2 pages : bloquer

		m_fEdit==TRUE || m_fNew==TRUE*/)
	{
		// TEST : si liste vide -> désactiver
		EnableWindow(FALSE);
		
		GetButtonDel()->EnableWindow(FALSE);
	}
	else
		GetButtonDel()->EnableWindow(TRUE);
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
	// gestion des boutons "Monter" et "Descendre"
	if(nCount<2 /*|| m_fEdit==TRUE || m_fNew==TRUE*/) // il faut au moins 2 items, ni édition, ni nouveau...
	{
		GetButtonUp()->EnableWindow(FALSE);
		GetButtonDown()->EnableWindow(FALSE);
	}
/////////////////////////////////////////////////////////////////////
	else
	{
		int nCurSel = GetCurSel();
		//ASSERT(nCurSel!=LB_ERR);
		// activer, on désactive ensuite si nécessaire (plus simple...)

		if(nCurSel==0)
		{
			GetButtonUp()->EnableWindow(FALSE);
			GetButtonDown()->EnableWindow(TRUE);
		}
		else
			if(nCurSel==nCount-1)
			{
				GetButtonUp()->EnableWindow(TRUE);
				GetButtonDown()->EnableWindow(FALSE);
			}
			else
			{
				GetButtonUp()->EnableWindow(TRUE);
				GetButtonDown()->EnableWindow(TRUE);
			}
	}
}

void CListboxUpDown3::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bEnableDragAndDrop)
	{
		CListBox::OnLButtonDown(nFlags, point);
		return;
	}

	SHRGINFO shrgi = {0};

    shrgi.cbSize        = sizeof(SHRGINFO);
    shrgi.hwndClient    = m_hWnd;
    shrgi.ptDown.x      = point.x;
    shrgi.ptDown.y      = point.y;
    shrgi.dwFlags       = SHRG_RETURNCMD;

    if(GN_CONTEXTMENU == ::SHRecognizeGesture(&shrgi))
	{
		//clear all the flags
		m_nMovingIndex = LB_ERR;
		m_nMoveToIndex = LB_ERR;
		m_fCaptured = FALSE;
		m_dwInterval = 0;
		BOOL bOutside;
		m_fDrag=TRUE;
		//find the item that they want to drag
		//and keep track of it. Later in the mouse move
		//we will capture the mouse if this value is set
		int nIndex = ItemFromPoint(point, bOutside);

		if(nIndex != LB_ERR && !bOutside)
		{
			m_nMovingIndex = nIndex;
			SetCurSel(nIndex);
			// léger bug d'affichage à cause du curseur à points
			DrawTheLines(nIndex);
		}
	}
        //ContextMenu(point);
    else
	{
		m_fDrag=FALSE;
        Default();
	}

	//CListBox::OnLButtonUp(nFlags, point);
}

void CListboxUpDown3::OnMouseMove(UINT nFlags, CPoint point)
{
	CListBox::OnMouseMove(nFlags, point);

	if(!m_bEnableDragAndDrop)
		return;

	if(!m_fDrag)
		return;

	if (nFlags & MK_LBUTTON)
	{
		if (m_nMovingIndex != LB_ERR && !m_fCaptured)
		{
			SetCapture();
			m_fCaptured = TRUE;
		}

		BOOL bOutside;
		int nIndex = ItemFromPoint(point, bOutside);

		//if they our not on a particular item
		if(bOutside)
		{
			CRect rcClient;
			GetClientRect(rcClient);

			//if they are still within the listbox window, then
			//simply select the last item as the drop point
			//else if they are outside the window then scroll the items
			if(rcClient.PtInRect(point))
			{
				KillTimer(TID_SCROLLDOWN);
				KillTimer(TID_SCROLLUP);
				m_dwInterval = 0;
				nIndex = LB_ERR;
				bOutside = FALSE;
			}
			else
			{
				DoTheScrolling(point, rcClient);
			}
		}
		else
		{
			KillTimer(TID_SCROLLDOWN);
			KillTimer(TID_SCROLLUP);
			m_dwInterval = 0;
		}

		if (nIndex != m_nMoveToIndex && !bOutside)
		{
			DrawTheLines(nIndex);
		}
	}
}

void CListboxUpDown3::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(!m_bEnableDragAndDrop)
	{
		CListBox::OnLButtonUp(nFlags, point);
		return;
	}

	if(m_fDrag && m_nMovingIndex!=LB_ERR && m_fCaptured)
	{
		KillTimer(TID_SCROLLDOWN);
		KillTimer(TID_SCROLLUP);
		m_dwInterval = 0;
		m_fCaptured = FALSE;
		ReleaseCapture();

		CRect rcClient;
		GetClientRect(rcClient);
		//if they are still within the listbox window
		if(rcClient.PtInRect(point))
		{
			InsertDraggedItem();
		}
		// supprimé car bug d'affichage : la barre d'insertion n'est pas éliminée (mauvais dessin)
		// si on abandonne le drag
		//else
		{
			Invalidate();
			UpdateWindow();
		}

		m_nMovingIndex = LB_ERR;
		m_nMoveToIndex = LB_ERR;
	}
	
	m_fDrag=FALSE;

	CListBox::OnLButtonUp(nFlags, point);
}

void CListboxUpDown3::OnTimer(UINT_PTR nIDEvent)
{
   if(nIDEvent == TID_SCROLLDOWN)
   {
      DrawTheLines(m_nMoveToIndex+1);
      SetTopIndex(GetTopIndex()+1);
   }
   else
	   if (nIDEvent == TID_SCROLLUP)
	   {
		  DrawTheLines(m_nMoveToIndex-1);
		  SetTopIndex(GetTopIndex()-1);
	   }

   CListBox::OnTimer(nIDEvent);
}

void CListboxUpDown3::DrawTheLines(int nIndex)
{
	CRect rcClient;
	GetClientRect(rcClient);
	CDC* pDC = GetDC();
	CRect rc;
	int cyLine=2*GetSystemMetrics(SM_CYBORDER);

//	if (m_nMoveToIndex != m_nMovingIndex)
	{
		CPen Pen(PS_SOLID, cyLine, RGB(255,255,255));
		CPen *pOldPen = pDC->SelectObject(&Pen);

		if(m_nMoveToIndex != LB_ERR)
		{
			GetItemRect(m_nMoveToIndex, rc);
			if(rcClient.PtInRect(rc.TopLeft()))
			{
			pDC->MoveTo(rc.left, rc.top+1);
			pDC->LineTo(rc.right-(cyLine/2), rc.top+1);
			}
		}
		else
		{
			GetItemRect(GetCount()-1, rc);

			if (rcClient.PtInRect(CPoint(0, rc.bottom)))
			{
				pDC->MoveTo(rc.left, rc.bottom);
				pDC->LineTo(rc.right-(cyLine/2), rc.bottom);
			}
		}

		pDC->SelectObject(pOldPen);
	}

	m_nMoveToIndex = nIndex;

//	if (m_nMoveToIndex != m_nMovingIndex)
	{
		CPen Pen(PS_SOLID, cyLine, RGB(0,0,0));
		CPen *pOldPen = pDC->SelectObject(&Pen);

		if(m_nMoveToIndex != LB_ERR)
		{
			GetItemRect(nIndex, rc);
			if(rcClient.PtInRect(rc.TopLeft()))
			{
				pDC->MoveTo(rc.left, rc.top+1);
				pDC->LineTo(rc.right-(cyLine/2), rc.top+1);
			}
		}
		else
		{
			GetItemRect(GetCount()-1, rc);

			if(rcClient.PtInRect(CPoint(0, rc.bottom)))
			{
				pDC->MoveTo(rc.left, rc.bottom);
				pDC->LineTo(rc.right-(cyLine/2), rc.bottom);
			}
		}

		pDC->SelectObject(pOldPen);
	}

	ReleaseDC(pDC);
}

void CListboxUpDown3::InsertDraggedItem()
{
	CString str;
	GetText(m_nMovingIndex, str);
	DWORD_PTR dwItemData = GetItemData(m_nMovingIndex);

	if (m_nMovingIndex < m_nMoveToIndex)
	{
		SetRedraw(FALSE);
		int nTopIndex = GetTopIndex();
		int nNewIndex = InsertString(m_nMoveToIndex, str);
		SetItemData(nNewIndex, dwItemData);
		DeleteString(m_nMovingIndex);
		SetCurSel(nNewIndex-1);
		SetTopIndex(nTopIndex);
		SetRedraw(TRUE);
		//we have to redraw the window since we are deleting a string
		//after we set the current selection. DeleteString causes a 
		//focus rect to show up under the current selection
		Invalidate();
		UpdateWindow();
	}
	else 
		if (m_nMovingIndex > m_nMoveToIndex)
		{
			SetRedraw(FALSE);
			int nTopIndex = GetTopIndex();
			DeleteString(m_nMovingIndex);
			int nNewIndex = InsertString(m_nMoveToIndex, str);
			SetItemData(nNewIndex, dwItemData);
			SetCurSel(nNewIndex);
			SetTopIndex(nTopIndex);
			SetRedraw(TRUE);
			//we have to redraw the window since we are deleting a string
			//after we set the current selection. DeleteString causes a 
			//focus rect to show up under the current selection
			Invalidate();
			UpdateWindow();
		}

	// le plus simple : reconstruire la CNamedObList à partir de la listbox
	m_pNamedObList->RemoveAll();
	int nCount=GetCount();
	for(int i=0; i<nCount; i++)
	{
		CObjNamed* pObj=(CObjNamed*)GetItemDataPtr(i);
		m_pNamedObList->AddTail(pObj);
	}
	
	GetParent()->SendMessage(WMU_LBUPDOWN_DRAGGED,MAKEWPARAM(GetDlgCtrlID(),0),(LPARAM)m_hWnd);
	GetParent()->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),LBN_SELCHANGE),(LPARAM)m_hWnd);
}

void CListboxUpDown3::DoTheScrolling(CPoint Point,CRect ClientRect)
{
   if (Point.y > ClientRect.Height())
   {
      DWORD Interval = 250 / (1+ ((Point.y-ClientRect.Height())/GetItemHeight(0)));
      if (Interval != m_dwInterval)
      {
         m_dwInterval = Interval;
         SetTimer(TID_SCROLLDOWN,Interval,NULL);
         OnTimer(TID_SCROLLDOWN);
      }
   }
   else if (Point.y < 0)
   {
      DWORD Interval = 250 / (1+(abs(Point.y)/GetItemHeight(1)));
      if (Interval != m_dwInterval)
      {
         m_dwInterval = Interval;
         SetTimer(TID_SCROLLUP,Interval,NULL);
         OnTimer(TID_SCROLLUP);
      }
   }
   else
   {
      KillTimer(TID_SCROLLDOWN);
      KillTimer(TID_SCROLLUP);
      m_dwInterval = 0;
   }
}

