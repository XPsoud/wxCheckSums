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

void CheckSums::Update(const unsigned char* buf, wxUint32 length)
{
	m_md5.Update(buf, length);
}

void CheckSums::Finalize()
{
	m_md5.Finalize();
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
