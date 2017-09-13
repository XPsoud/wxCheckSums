#ifndef __WXMD5_H_INCLUDED__
#define __WXMD5_H_INCLUDED__

#include <wx/wx.h>

#include "md5.h"

class wxMD5
{
	public:
		wxMD5(const wxString& text=wxEmptyString);
		~wxMD5();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		bool m_bFinalized;
		uint8_t m_uiDigest[MD5_DIGEST_SIZE];
		md5_ctx m_context;
};

#endif // __WXMD5_H_INCLUDED__
