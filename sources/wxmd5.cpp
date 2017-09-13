#include "wxmd5.h"

wxMD5::wxMD5(const wxString& text)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxMD5\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxMD5::~wxMD5()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxMD5\" object\n"));
#endif // __WXDEBUG__
}

void wxMD5::Initialize()
{
	md5_init_ctx(&m_context);

	m_bFinalized=false;
}

// Continue an MD5 message-digest operation, processing another message block
void wxMD5::Update(const unsigned char *message, unsigned int len)
{
	md5_process_bytes(message, len, &m_context);
}

// End an MD5 message-digest operation, writing the digest and zeroizing the context.
void wxMD5::Finalize()
{
	md5_finish_ctx(&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxMD5::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (int i=0; i<MD5_DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}
