#include "checksums.h"

const wxChar* szHashNames[HT_COUNT] = { _("MD5"), _("SHA1"),
										_("SHA224"), _("SHA256"),
										_("SHA384"), _("SHA512") };

CheckSums::CheckSums(const wxString& text) :
	m_md5(text), m_sha1(text), m_sha224(text),
	m_sha256(text), m_sha384(text), m_sha512(text)
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
	m_sha224.Update(buf, length);
	m_sha256.Update(buf, length);
	m_sha384.Update(buf, length);
	m_sha512.Update(buf, length);
}

void CheckSums::Finalize()
{
	m_md5.Finalize();
	m_sha1.Finalize();
	m_sha224.Finalize();
	m_sha256.Finalize();
	m_sha384.Finalize();
	m_sha512.Finalize();
}

wxString CheckSums::GetHexDigest(HashType type)
{
	switch(type)
	{
		case HT_MD5:
			return m_md5.HexDigest();
		case HT_SHA1:
			return m_sha1.HexDigest();
		case HT_SHA224:
			return m_sha224.HexDigest();
		case HT_SHA256:
			return m_sha256.HexDigest();
		case HT_SHA384:
			return m_sha384.HexDigest();
		case HT_SHA512:
			return m_sha512.HexDigest();
		default:
			return wxEmptyString;
	}
}
