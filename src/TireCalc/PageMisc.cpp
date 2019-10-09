// PageMementoTireCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageMisc.h"

// Boîte de dialogue CPageMisc

// http://www.tirerack.com/tires/tiretech/techpage.jsp?techid=23

typedef struct OtherMarking
{
	TCHAR szCode[32];
	TCHAR szExpl[256];
} t_OtherMarking;

t_OtherMarking otherMarkingArray[]=
{
	{ _T("GZ"), _T("Homologation Subaru") },
	{ _T("DZ"), _T("Homologation Honda / Mazda / Toyota") },
	{ _T("A"), _T("Homologation Renault Espace IV 18") },
	{ _T("Alfa Romeo"), _T("Homologation Alfa Romeo") },
	{ _T("AM8"), _T("Homologation Aston Martin") },
	{ _T("AM9"), _T("Homologation Aston Martin DB9 Volante VA V8") },
	{ _T("AMS"), _T("Homologation Aston Martin") },
	{ _T("AO"), _T("Homologation Audi") },
	{ _T("AU"), _T("Homologation Audi") },
	{ _T("AZ"), _T("Homologation Alfa Romeo / Fiat / Subaru / Toyota") },
	{ _T("B"), _T("(B entouré d'un cercle) Homologation Bentley") },
	{ _T("B1"), _T("Homologation Bentley") },
	{ _T("C1"), _T("Homologation Chrysler Viper") },
	{ _T("EZ"), _T("Homologation Audi / Mazda 6") },
	{ _T("Ferrari"), _T("Homologation Ferrari") },
	{ _T("Ferrari-Maserati"), _T("Homologation Ferrari/Maserati") },
	{ _T("FO"), _T("Homologation Ford") },
	{ _T("H0"), _T("Homologation Honda Acura NSX") },
	{ _T("H1"), _T("Homologation Honda Acura NSX") },
//	{ _T("J"), _T("Homologation Jaguar") },
	{ _T("JZ"), _T("Homologation Seat / Subaru") },
	{ _T("K1"), _T("Homologation Ferrari") },
	{ _T("K2"), _T("Homologation Ferrari") },
	{ _T("KZ"), _T("Homologation Nissan / Toyota") },
	{ _T("L"), _T("Homologation Lamborghini") },
	{ _T("LRO"), _T("Homologation Land Rover") },
	{ _T("LZ"), _T("Homologation Lancia") },
	{ _T("M0"), _T("Homologation Mercedes") },
	{ _T("M01"), _T("Homologation Mercedes SL65 AMG") },
	{ _T("M0Extended"), _T("Homologation Mercedes Extended (Runflat)") },
	{ _T("MB"), _T("Homologation Mercedes") },
	{ _T("A-M0"), _T("Homologation Mercedes") },
	{ _T("MZ"), _T("Homologation Mitsubishi / Toyota") },
	{ _T("N0"), _T("Homologation Porsche") },
	{ _T("N1"), _T("Homologation Porsche") },
	{ _T("N2"), _T("Homologation Porsche") },
	{ _T("N3"), _T("Homologation Porsche") },
	{ _T("N4"), _T("Homologation Porsche") },
	{ _T("N5"), _T("Homologation Porsche") },
	{ _T("N6"), _T("Homologation Porsche") },
	{ _T("SZ"), _T("Homologation Mazda MPV") },
	{ _T("TZ"), _T("Homologation Mazda 6") },
	{ _T("UZ"), _T("Homologation BMW 3 / Skoda") },
	{ _T("VO"), _T("Homologation Volkswagen") },
	{ _T("VW"), _T("Homologation Volkswagen") },
	{ _T("B"), _T("Homologation Audi") },
	{ _T("AU"), _T("Homologation Audi") },
	{ _T("J"), _T("(J entouré d'un cercle) Homologation Jaguar") },
	{ _T("*"), _T("(étoile à 5 branches) Homologation BMW") },
	{ _T("PE"), _T("Homologation Peugeot") },
	{ _T("PZ"), _T("Homologation Ford / Mazda / Mercedes / VW") },
	{ _T("QZ"), _T("Homologation Mini") },
	{ _T("CZ"), _T("Homologation Subaru") },
	{ _T("G"), _T("Homologation Volkswagen Golf") },
	{ _T("TO"), _T("Homologation Toyota") },
	{ _T("R01"), _T("Homologation Audi Quattro, RS4, RS6, R8") },
	{ _T("LTS"), _T("Homologation Lotus") },


	{ _T("BZ"), _T("monte d'origine Bridgestone") },
	{ _T("1Z"), _T("Monte d'origine Bridgestone") },
	{ _T("2Z"), _T("Monte d'origine Bridgestone") },
	{ _T("3Z"), _T("Monte d'origine Bridgestone") },
	{ _T("FZ"), _T("Monte d'origine Bridgestone") },
	{ _T("HZ"), _T("Monte d'origine Bridgestone") },
	{ _T("RZ"), _T("Monte d'origine Bridgestone") },
	{ _T("VZ"), _T("Monte d'origine Bridgestone") },
	{ _T("WZ"), _T("Monte d'origine Bridgestone") },
	{ _T("XZ"), _T("Monte d'origine Bridgestone") },
	{ _T("YZ"), _T("Monte d'origine Bridgestone") },
	{ _T("NZ"), _T("Monte d'origine Bridgestone") },
	{ _T("OZ"), _T("Monte d'origine Bridgestone") },


	//{ _T("(R02)"), _T("") },
	//{ _T("A"), _T("") },
	//{ _T("AML"), _T("") },
	//{ _T("AMR"), _T("") },
	//{ _T("(F)"), _T("") },
	//{ _T("FI"), _T("") },
	//{ _T("MH"), _T("") },
	//{ _T("H"), _T("") },
	//{ _T("JRS"), _T("") },
	//{ _T("LRR"), _T("") },
	//{ _T("LTS"), _T("") },
	//{ _T("m"), _T("") },
	//{ _T("M"), _T("") },
	//{ _T("MC1"), _T("") },
	//{ _T("S"), _T("") },
	//{ _T("S1"), _T("") },
	//{ _T("S2"), _T("") },
	//{ _T("S78"), _T("") },
	//{ _T("SS"), _T("") },
	//{ _T("WET"), _T("") },
	//{ _T("WTCC"), _T("") },


	{ _T("RunFlat"), _T("Pneu permettant de rouler en cas de crevaison") },
	{ _T("RunFL"), _T("Pneu permettant de rouler en cas de crevaison") },
	{ _T("EUFORI"), _T("Pneu permettant de rouler en cas de crevaison") },
	{ _T("RFT"), _T("Pneu permettant de rouler en cas de crevaison") },

	{ _T("EMT"), _T("Goodyear Extended Mobility Tire prévus pour rouler à plat") },
	{ _T("DSST"), _T("Dunlop Self-Supporting Technology run-flat tires, prévus pour rouler à plat") },
	{ _T("Pax"), _T("Michelin : Pneu permettant rouler sur 200km à 80km/h en cas de perte de pression par Michelin") },
	{ _T("ZP"), _T("Michelin ZP : runflat, pneu permettant de rouler 80 km maximum à 80 km/heure") },
	{ _T("SSR"), _T("Self-Supporting Run-Flat Tyre ou pneu à flancs porteurs. Pneu permettant de rouler 80 km maximum à 80 km/heure. Les pneus SSR imposent un système de contrôle de pression") },
	{ _T("HRS"), _T("Hankook Runflat System") },

	{ _T("Demo"), _T("Pneu déjà monté et démonté, neuf et garanti") },
	{ _T("Demont"), _T("Pneu déjà monté et démonté, neuf et garanti") },
	{ _T("DEMO"), _T("Pneus montés et démontés pouvant avoir roulé quelques mètres. Ces pneus sont garantis et neufs") },

	{ _T("4-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("6-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("8-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("10-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("12-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("14-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("16-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	{ _T("18-PR"), _T("Ply Rating : indice de capacité de charge. Sans relation directe avec le nombre de plis") },
	
	{ _T("CD"), _T("Self-selling standard production tyres") },
	{ _T("Conti-Seal"), _T("Self-selling standard production tyres") },

	{ _T("C"), _T("Pneu pour pour véhicules utilitaires et camionnettes") },
	{ _T("DA"), _T("Pneus avec défaut d'aspect, deuxième choix avec les mêmes garanties fabricant") },
	{ _T("DT"), _T("Different Tread Design") },
	{ _T("DT1"), _T("Nouvelle version du profil du pneu") },
	{ _T("G1"), _T("Diamètre extérieur où la largeur de bande de roulement diffère du même pneu sans marquage G1. Il faut obligatoirement monter 4 pneus en G1 si le véhicule a 4 roues motrices") },
	{ _T("K1"), _T("Gomme K1") },
	{ _T("M+S"), _T("Mud & Snow (boue et neige) : Pneu Hiver") },
	{ _T("NHS"), _T("Not for Highway Service") },
	{ _T("Seal"), _T("Self-selling standard production tyres") },

	{ _T("TL"), _T("Tubeless, pneu sans chambre à air") },
	{ _T("TT"), _T("Tubetype, pneu avec chambre à air") },
	{ _T("Tubeless"), _T("Tubeless, pneu sans chambre à air") },
	{ _T("Tubetype"), _T("Tubetype, pneu avec chambre à air") },

	{ _T("MFS"), _T("Max Flange Shield : renfort de protection pour bord de jante") },
	{ _T("FP"), _T("Bord de protection jante alu") },
	{ _T("FR"), _T("Protection jante") },
	{ _T("FSL"), _T("Protection de rebord de jante") },
	{ _T("RPB"), _T("Rim Protection Bar") },

	{ _T("SPIKE"), _T("Pneus cloutables") },
	{ _T("STUDDABLE"), _T("Pneus cloutables. Montage par 4. Pneus soumis à réglementation départementale") },

	{ _T("VSB"), _T("Vertical Serrated Band") },
	{ _T("SB"), _T("Serrated Black Stripe") },
	{ _T("SBL"), _T("Serrated Black Letter") },
	{ _T("RWL"), _T("Raised White Letter : lettres blanches en relief") },
	{ _T("OBL"), _T("Off Black Letter : contour des lettres noir") },
	{ _T("OWL"), _T("Off White Letter : lettres blanches") },
	{ _T("ORWL"), _T("Off White Letter : lettres blanches") },
	{ _T("OWT"), _T("Contour des lettres blanc") },
	{ _T("RB"), _T("Lettres noires, entouré de blanc.") },
	{ _T("RBL"), _T("Raised or Recessed Black Letters") },
	{ _T("RBT"), _T("Raised Black Letters Tubeless : lettres noires et en relief") },
	{ _T("RGL"), _T("Raised Gold Letters : lettres dorées en relief") },
	{ _T("WL"), _T("White letter : lettres blanches") },
	{ _T("WSW"), _T("White Sidewall : pneu à flanc blanc") },
	{ _T("WW"), _T("Pneu à flanc blanc") },
	{ _T("WWW"), _T("Pneu à flanc blanc") },
	{ _T("BL"), _T("Black Label : lettres noires") },
	{ _T("BSW"), _T("Black Side Wall : flanc noir") },
	{ _T("BS"), _T("Black Stylized") },


	{ _T("XL"), _T("Extra load : pneu renforcé, indice de charge supérieur au marquage standard") },
	{ _T("EL"), _T("Extra load : pneu renforcé, indice de charge supérieur au marquage standard") },
	{ _T("RF"), _T("Extra load : pneu renforcé, indice de charge supérieur au marquage standard") },

	{ _T("E3"), _T("Certifié aux normes européennes") }
};


IMPLEMENT_DYNAMIC(CPageMisc, CPropPageEx)

CPageMisc::CPageMisc()
	: CPropPageEx(CPageMisc::IDD, NULL)
{
	EnableScrollbars(TRUE);
}

CPageMisc::~CPageMisc()
{
}

void CPageMisc::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MISC, m_editMisc);
	DDX_Control(pDX, IDC_LIST_MISC, m_listMisc);
}


BEGIN_MESSAGE_MAP(CPageMisc, CPropPageEx)
	ON_LBN_SELCHANGE(IDC_LIST_MISC, &CPageMisc::OnLbnSelchangeListMisc)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageMisc

BOOL CPageMisc::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	for(int i=0; i < sizeof(otherMarkingArray)/sizeof(t_OtherMarking); i++)
	{
		CString str;
		str.Format(_T("%s"), otherMarkingArray[i].szCode);
		int n=m_listMisc.AddString(str);
		ASSERT(n>=0);
		m_listMisc.SetItemDataPtr(n, otherMarkingArray[i].szExpl);
	}
	
	m_listMisc.SetCurSel(0);
	OnLbnSelchangeListMisc();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageMisc::OnLbnSelchangeListMisc()
{
	int nCurSel=m_listMisc.GetCurSel();
	if(nCurSel!=LB_ERR)
	{
		LPTSTR psz=(LPTSTR)m_listMisc.GetItemDataPtr(nCurSel);
		CString str=psz;
		m_editMisc.SetWindowTextW(psz);
	}
}
