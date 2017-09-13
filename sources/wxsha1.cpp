#include "wxsha1.h"

wxSHA1::wxSHA1(const wxString& text)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA1\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA1::~wxSHA1()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA1\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA1::Initialize()
{
	sha1_init_ctx(&m_context);

	m_bFinalized=false;
}

void wxSHA1::Update(const unsigned char *message, unsigned int len)
{
	sha1_process_bytes(message, len, &m_context);
}

void wxSHA1::Finalize()
{
	sha1_finish_ctx (&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxSHA1::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (int i=0; i<SHA1_DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}
