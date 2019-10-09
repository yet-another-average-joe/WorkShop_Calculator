// WrkShpCalcDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "WrkShpCalc.h"
#include "WrkShpCalcDlg.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Boîte de dialogue CWrkShpCalcDlg

CWrkShpCalcDlg::CWrkShpCalcDlg(CWnd* pParent /*=NULL*/)
	: CDlgMain(CWrkShpCalcDlg::IDD)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWrkShpCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MATDB, m_btnMatDb);
	DDX_Control(pDX, IDC_BTN_DRILLCALC, m_btnDrillCalc);
	DDX_Control(pDX, IDC_BTN_LATHECALC, m_btnLatheCalc);
	DDX_Control(pDX, IDC_BTN_MILLCALC, m_btnMillCalc);
	DDX_Control(pDX, IDC_BTN_SYSCOLOR, m_btnSysColor);
	DDX_Control(pDX, IDC_BTN_SYSTEMMETRICS, m_btnSystemMetrics);
	DDX_Control(pDX, IDC_BTN_TAPCALC, m_btnTapCalc);
	DDX_Control(pDX, IDC_BTN_TIRECALC, m_btnTireCalc);
	DDX_Control(pDX, IDC_BTN_NEWTONCALC, m_btnNewtonCalc);
	DDX_Control(pDX, IDC_BTN_THUNDERCALC, m_btnThunderCalc);
	DDX_Control(pDX, IDC_BTN_PARSERCALC, m_btnParserCalc);
	DDX_Control(pDX, IDC_BTN_STOCKCALC, m_btnStockCalc);
}

BEGIN_MESSAGE_MAP(CWrkShpCalcDlg, CDlgMain)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_MATDB, &CWrkShpCalcDlg::OnBnClickedBtnMatdb)
	ON_BN_CLICKED(IDC_BTN_DRILLCALC, &CWrkShpCalcDlg::OnBnClickedBtnDrillcalc)
	ON_BN_CLICKED(IDC_BTN_LATHECALC, &CWrkShpCalcDlg::OnBnClickedBtnLathecalc)
	ON_BN_CLICKED(IDC_BTN_MILLCALC, &CWrkShpCalcDlg::OnBnClickedBtnMillcalc)
	ON_BN_CLICKED(IDC_BTN_SYSCOLOR, &CWrkShpCalcDlg::OnBnClickedBtnSysColor)
	ON_BN_CLICKED(IDC_BTN_SYSTEMMETRICS, &CWrkShpCalcDlg::OnBnClickedBtnSystemMetrics)
	ON_BN_CLICKED(IDC_BTN_TAPCALC, &CWrkShpCalcDlg::OnBnClickedBtnTapcalc)
	ON_BN_CLICKED(IDC_BTN_TIRECALC, &CWrkShpCalcDlg::OnBnClickedBtnTirecalc)
	ON_BN_CLICKED(IDC_BTN_THUNDERCALC, &CWrkShpCalcDlg::OnBnClickedBtnThundercalc)
	ON_BN_CLICKED(IDC_BTN_NEWTONCALC, &CWrkShpCalcDlg::OnBnClickedBtnNewtoncalc)
	ON_BN_CLICKED(IDC_BTN_PARSERCALC, &CWrkShpCalcDlg::OnBnClickedBtnParsercalc)
	ON_BN_CLICKED(IDC_BTN_STOCKCALC, &CWrkShpCalcDlg::OnBnClickedBtnStockcalc)
END_MESSAGE_MAP()


// Gestionnaires de messages pour CWrkShpCalcDlg

BOOL CWrkShpCalcDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	// désactiver "WrkShpCalc" dans le menu
	EnableWrkShpCalcBtn(m_hWnd, WRKSHPCALC_BTN_DISABLED);

	CSize size(3*::GetSystemMetrics(SM_CXSMICON), 3*::GetSystemMetrics(SM_CYSMICON));
	//CSize size(16, 16);
	m_btnMatDb.SetIconMulti(			IDI_MATDB,			IDI_MATDB,			size);
	m_btnDrillCalc.SetIconMulti(		IDI_DRILLCALC,		IDI_DRILLCALC,		size);
	m_btnLatheCalc.SetIconMulti(		IDI_LATHECALC,		IDI_LATHECALC,		size);
	m_btnTapCalc.SetIconMulti(			IDI_TAPCALC,		IDI_TAPCALC,		size);
	m_btnMillCalc.SetIconMulti(			IDI_MILLCALC,		IDI_MILLCALC,		size);
	m_btnSysColor.SetIconMulti(			IDI_SYSCOLOR,		IDI_SYSCOLOR,		size);
	m_btnSystemMetrics.SetIconMulti(	IDI_SYSTEMMETRICS,	IDI_SYSTEMMETRICS,	size);
	m_btnTireCalc.SetIconMulti(			IDI_TIRECALC,		IDI_TIRECALC,		size);
	m_btnNewtonCalc.SetIconMulti(		IDI_NEWTONCALC,		IDI_NEWTONCALC,		size);
	m_btnThunderCalc.SetIconMulti(		IDI_THUNDERCALC,	IDI_THUNDERCALC,	size);
	m_btnParserCalc.SetIconMulti(		IDI_PARSERCALC,		IDI_PARSERCALC,		size);
	m_btnStockCalc.SetIconMulti(		IDI_STOCKCALC,		IDI_STOCKCALC,		size);
	
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}


void CWrkShpCalcDlg::OnBnClickedBtnMatdb()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("MatDb.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnDrillcalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("Drillcalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnLathecalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("LatheCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnMillcalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("MillCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnSysColor()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("SysColor.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnSystemMetrics()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("SystemMetrics.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnTapcalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("Tapcalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnTirecalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("TireCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnThundercalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("ThunderCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnNewtoncalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("NewtonCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnParsercalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("ParserCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}

void CWrkShpCalcDlg::OnBnClickedBtnStockcalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("StockCalc.exe"); // pas besoin de placer en resource : invariable


	SHELLEXECUTEINFO ExecuteInfo;    
	memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
	    
	ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
	ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
	ExecuteInfo.hwnd         = 0;                
	ExecuteInfo.lpVerb       = _T("open");                      
	ExecuteInfo.lpFile       = strApp;
	ExecuteInfo.lpDirectory  = strAppDir;
	ExecuteInfo.nShow        = SW_SHOW;
	ExecuteInfo.hInstApp     = 0;    

	if(ShellExecuteEx(&ExecuteInfo) == FALSE)
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
}
