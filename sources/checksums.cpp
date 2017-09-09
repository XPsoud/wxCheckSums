#include "checksums.h"

const wxChar* szHashNames[HT_COUNT] = { _("MD5"), _("SHA1") };

CheckSums::CheckSums(const wxString& text) :
	m_md5(text), m_sha1(text)
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

void CheckSums::Update(const unsigned char* buf, uint32_t length)
{
	m_md5.Update(buf, length);
	m_sha1.Update(buf, length);
}

void CheckSums::Finalize()
{
	m_md5.Finalize();
	m_sha1.Finalize();
}

wxString CheckSums::GetHexDigest(HashType type)
{
	switch(type)
	{
		case HT_MD5:
			return m_md5.HexDigest();
		case HT_SHA1:
			return m_sha1.HexDigest();
		default:
			return wxEmptyString;
	}
}
