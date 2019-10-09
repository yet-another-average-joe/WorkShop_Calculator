#include "stdafx.h"
#include "DecimalSupport.h"

void DecimalToText(TCHAR* szBuff, size_t buflen , const char* digits, int decimal_pos, BOOL sign);
void DisplayDecimalValue(const char* digits, int decimal_pos, int sign);


BOOL TextToDouble(TCHAR* szBuff, double& d)
{
	/// the locale dependant decimal separator
	TCHAR DecimalSeparator[5];
	
	// memeset ajouté pour empêcher le compil de gueuler
	memset( DecimalSeparator, 0, sizeof(DecimalSeparator) ); 

	::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, DecimalSeparator , sizeof(DecimalSeparator) / sizeof(TCHAR));
	/// the locale dependant negative sign
	TCHAR NegativeSign[6];

	// memeset ajouté pour empêcher le compil de gueuler
	memset( NegativeSign, 0, sizeof(DecimalSeparator) ); 

	::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, DecimalSeparator , sizeof(DecimalSeparator) / sizeof(TCHAR));

	//replace the locale dependant separator with.
	if (DecimalSeparator[0] != _T('.'))
	{
		for (TCHAR* x = szBuff; *x; ++x)
		{
			if (*x == DecimalSeparator[0])
			{
				*x = _T('.');
				break;
			}
		}

	}
	
	TCHAR* endPtr;
	//replace the negative sign with -
	if (szBuff[0] == NegativeSign[0]) szBuff[0] = _T('-');
	d = _tcstod(szBuff, &endPtr);
	return *endPtr == _T('\0');
}


void DoubleToText(LPTSTR lpstr, double d, int count)
{
		int decimal_pos;
		int sign;
		
		//#if _MSC_VER >= 1400
//		char digits[limit];
//		_ecvt_s(digits,d,count,&decimal_pos,&sign);
//#else
		char* digits = _ecvt(d,count,&decimal_pos,&sign);
//#endif

		DisplayDecimalValue(digits, decimal_pos, sign);
}

void DoubleToText(CString& str, double d, int count)
{
		int decimal_pos;
		int sign;
		
		//#if _MSC_VER >= 1400
//		char digits[limit];
//		_ecvt_s(digits,d,count,&decimal_pos,&sign);
//#else
		char* digits = _ecvt(d,count,&decimal_pos,&sign);
//#endif

		TCHAR szBuff[_CVTBUFSIZE];
		DecimalToText(szBuff, _CVTBUFSIZE , digits, decimal_pos, sign);
//		static_cast<T*>(this)->SetWindowText(szBuff);
		str=szBuff;
}

void SetDecimalValue(double d, int count)
	{
		int decimal_pos;
		int sign;
		
		//#if _MSC_VER >= 1400
//		char digits[limit];
//		_ecvt_s(digits,d,count,&decimal_pos,&sign);
//#else
		char* digits = _ecvt(d,count,&decimal_pos,&sign);
//#endif

		DisplayDecimalValue(digits, decimal_pos, sign);
}

	/// sets the controls text
	/// \param[in] digits array containing the digits
	/// \param[in] decimal_pos the position of the decimal point
	/// \param[in] sign 1 if negative
	
void DisplayDecimalValue(const char* digits, int decimal_pos, int sign)
{
		TCHAR szBuff[_CVTBUFSIZE];
		DecimalToText(szBuff, _CVTBUFSIZE , digits, decimal_pos, sign);
//		static_cast<T*>(this)->SetWindowText(szBuff);
}


	/// convert a digit array to string
	/// \param[out] szBuff target buffer for output
	/// \param[in] buflen maximum characters in output buffer
	/// \param[in] digits array containing the digits
	/// \param[in] decimal_pos the position of the decimal point
	/// \param[in] sign 1 if negative
	
void DecimalToText(TCHAR* szBuff, size_t buflen , const char* digits, int decimal_pos, BOOL sign)
{
	/// the locale dependant decimal separator
	TCHAR DecimalSeparator[5];
	::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, DecimalSeparator , sizeof(DecimalSeparator) / sizeof(TCHAR));
	/// the locale dependant negative sign
	TCHAR NegativeSign[6];
	::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, DecimalSeparator , sizeof(DecimalSeparator) / sizeof(TCHAR));

	int i = 0;
	size_t pos = 0;
	if (sign)
	{
		for (const TCHAR *x =NegativeSign; *x ; ++x , ++pos) szBuff[pos] = *x;
	}
	
	for (; pos < buflen && digits[i] && i < decimal_pos ; ++i , ++pos) szBuff[pos] = digits[i];
	
	if (decimal_pos < 1) szBuff[pos++] = _T('0');
	size_t last_nonzero = pos;

	for (const TCHAR *x = DecimalSeparator; *x ; ++x , ++pos) szBuff[pos] = *x;
	for (; pos < buflen && decimal_pos < 0; ++decimal_pos , ++pos) szBuff[pos] = _T('0');

	for (; pos < buflen && digits[i]; ++i , ++pos) 
	{
		szBuff[pos] = digits[i];
		if (digits[i] != '0') last_nonzero = pos+1;
	}
	szBuff[min(buflen - 1,last_nonzero)] = _T('\0');		
}
