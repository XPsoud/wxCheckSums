#ifndef __WXSHA1_H_INCLUDED__
#define __WXSHA1_H_INCLUDED__

#include <wx/wx.h>

#include "sha1.h"

class wxSHA1
{
	public:
		wxSHA1(const wxString& text=wxEmptyString);
		~wxSHA1();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		uint8_t m_uiDigest[SHA1_DIGEST_SIZE];
		bool m_bFinalized;
		sha1_ctx m_context;
};

#endif /* __WXSHA1_H_INCLUDED__ */
