#ifndef __WXSHA2_H_INCLUDED__
#define __WXSHA2_H_INCLUDED__

#include <wx/wx.h>

#include "sha256.h"
#include "sha512.h"

class wxSHA2
{
	public:
		wxSHA2();
		virtual ~wxSHA2();
		virtual void Initialize() = 0;
		virtual void Update(const unsigned char *message, unsigned int len) = 0;
		virtual void Finalize() = 0;
	protected:
		bool m_bFinalized;
};

class wxSHA224 : public wxSHA2
{
	public:
		wxSHA224(const wxString& text=wxEmptyString);
		virtual ~wxSHA224();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		static const uint32_t DIGEST_SIZE = ( 224 / 8);
		uint8_t m_uiDigest[DIGEST_SIZE];
		sha256_ctx m_context;
};

class wxSHA256 : public wxSHA2
{
	public:
		wxSHA256(const wxString& text=wxEmptyString);
		virtual ~wxSHA256();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	protected:
	private:
		void Initialize();
		static const uint32_t DIGEST_SIZE = ( 256 / 8);
		uint8_t m_uiDigest[DIGEST_SIZE];
		sha256_ctx m_context;
};

class wxSHA384 : public wxSHA2
{
	public:
		wxSHA384(const wxString& text=wxEmptyString);
		virtual ~wxSHA384();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		static const uint32_t DIGEST_SIZE = ( 384 / 8);
		uint8_t m_uiDigest[DIGEST_SIZE];
		sha512_ctx m_context;
};

class wxSHA512 : public wxSHA2
{
	public:
		wxSHA512(const wxString& text=wxEmptyString);
		virtual ~wxSHA512();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	protected:
	private:
		void Initialize();
		static const uint32_t DIGEST_SIZE = ( 512 / 8);
		uint8_t m_uiDigest[DIGEST_SIZE];
		sha512_ctx m_context;
};

#endif // __WXSHA2_H_INCLUDED__
