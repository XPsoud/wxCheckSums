#include "checksums.h"

CheckSums::CheckSums(const wxString& text) :
	m_md5(text)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"CheckSums\" object\n"));
#endif // __WXDEBUG__
}

CheckSums::~CheckSums()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"CheckSums\" object\n"));
#endif // __WXDEBUG__
}

wxString CheckSums::GetHexDigest(HashType type)
{
	switch(type)
	{
		case HT_MD5:
			return m_md5.HexDigest();
		default:
			return wxEmptyString;
	}
}
