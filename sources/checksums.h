#ifndef __CHECKSUMS_H_INCLUDED__
#define __CHECKSUMS_H_INCLUDED__

#include <wx/wx.h>

#include "wxmd5.h"
#include "wxsha1.h"
#include "wxsha2.h"

enum HashType
{
	HT_UNKNOWN = -1,
	HT_MD5,
	HT_SHA1,
	HT_SHA224,
	HT_SHA256,
	HT_SHA384,
	HT_SHA512,

	HT_COUNT
};

extern const wxChar* szHashNames[HT_COUNT];

class CheckSums
{
	public:
		CheckSums(const wxString& text=wxEmptyString);
		virtual ~CheckSums();
		void Update(const unsigned char *buf, uint32_t length);
		void Finalize();
		wxString GetHexDigest(HashType type);
	protected:
	private:
		wxMD5 m_md5;
		wxSHA1 m_sha1;
		wxSHA224 m_sha224;
		wxSHA256 m_sha256;
		wxSHA384 m_sha384;
		wxSHA512 m_sha512;
};

#endif // __CHECKSUMBASE_H_INCLUDED__
