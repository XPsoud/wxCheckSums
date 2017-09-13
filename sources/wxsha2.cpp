#include "wxsha2.h"

wxSHA2::wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA2\" object\n"));
#endif // __WXDEBUG__
}

wxSHA2::~wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA2\" object\n"));
#endif // __WXDEBUG__
}

wxSHA224::wxSHA224(const wxString& text) : wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA224\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA224::~wxSHA224()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA224\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA224::Initialize()
{
	sha224_init_ctx(&m_context);

	m_bFinalized=false;
}

void wxSHA224::Update(const unsigned char *message, unsigned int len)
{
	sha256_process_bytes(message, len, &m_context);
}

void wxSHA224::Finalize()
{
	sha224_finish_ctx (&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxSHA224::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (size_t i=0; i<DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}

wxSHA256::wxSHA256(const wxString& text) : wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA256\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA256::~wxSHA256()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA256\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA256::Initialize()
{
	sha256_init_ctx(&m_context);

	m_bFinalized=false;
}

void wxSHA256::Update(const unsigned char *message, unsigned int len)
{
	sha256_process_bytes(message, len, &m_context);
}

void wxSHA256::Finalize()
{
	sha256_finish_ctx (&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxSHA256::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (size_t i=0; i<DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}

wxSHA384::wxSHA384(const wxString& text) : wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA384\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA384::~wxSHA384()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA384\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA384::Initialize()
{
	sha384_init_ctx(&m_context);

	m_bFinalized=false;
}

void wxSHA384::Update(const unsigned char *message, unsigned int len)
{
	sha512_process_bytes(message, len, &m_context);
}

void wxSHA384::Finalize()
{
	sha384_finish_ctx (&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxSHA384::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (size_t i=0; i<DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}

wxSHA512::wxSHA512(const wxString& text) : wxSHA2()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA512\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA512::~wxSHA512()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA512\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA512::Initialize()
{
	sha512_init_ctx(&m_context);

	m_bFinalized=false;
}

void wxSHA512::Update(const unsigned char *message, unsigned int len)
{
	sha512_process_bytes(message, len, &m_context);
}

void wxSHA512::Finalize()
{
	sha512_finish_ctx (&m_context, m_uiDigest);

	m_bFinalized=true;
}

wxString wxSHA512::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (size_t i=0; i<DIGEST_SIZE; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}
