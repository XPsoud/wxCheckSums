#include "checksums.h"

#include "settingsmanager.h"

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
	SettingsManager& options=SettingsManager::Get();
	for (int i=0; i<HT_COUNT; ++i)
		m_bHash[i]=options.GetHashMethodEnabled((HashType)i);
}

CheckSums::~CheckSums()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"CheckSums\" object\n"));
#endif // __WXDEBUG__
}

bool CheckSums::EnableHashType(HashType type, bool enable)
{
	if ((type <= HT_UNKNOWN) || (type >= HT_COUNT))
		false;

	m_bHash[type]=enable;

	return true;
}

void CheckSums::Update(const unsigned char* buf, uint32_t length)
{
	if (m_bHash[HT_MD5])
		m_md5.Update(buf, length);
	if (m_bHash[HT_SHA1])
		m_sha1.Update(buf, length);
	if (m_bHash[HT_SHA224])
		m_sha224.Update(buf, length);
	if (m_bHash[HT_SHA256])
		m_sha256.Update(buf, length);
	if (m_bHash[HT_SHA384])
		m_sha384.Update(buf, length);
	if (m_bHash[HT_SHA512])
		m_sha512.Update(buf, length);
}

void CheckSums::Finalize()
{
	if (m_bHash[HT_MD5])
		m_md5.Finalize();
	if (m_bHash[HT_SHA1])
		m_sha1.Finalize();
	if (m_bHash[HT_SHA224])
		m_sha224.Finalize();
	if (m_bHash[HT_SHA256])
		m_sha256.Finalize();
	if (m_bHash[HT_SHA384])
		m_sha384.Finalize();
	if (m_bHash[HT_SHA512])
		m_sha512.Finalize();
}

wxString CheckSums::GetHexDigest(HashType type)
{
	switch(type)
	{
		case HT_MD5:
			if (m_bHash[HT_MD5])
				return m_md5.HexDigest();
			break;
		case HT_SHA1:
			if (m_bHash[HT_SHA1])
				return m_sha1.HexDigest();
			break;
		case HT_SHA224:
			if (m_bHash[HT_SHA224])
				return m_sha224.HexDigest();
			break;
		case HT_SHA256:
			if (m_bHash[HT_SHA256])
				return m_sha256.HexDigest();
			break;
		case HT_SHA384:
			if (m_bHash[HT_SHA384])
				return m_sha384.HexDigest();
			break;
		case HT_SHA512:
			if (m_bHash[HT_SHA512])
				return m_sha512.HexDigest();
			break;
		default:
			return wxEmptyString;
	}
	return wxEmptyString;
}
