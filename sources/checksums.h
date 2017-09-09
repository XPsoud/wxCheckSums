#ifndef __CHECKSUMS_H_INCLUDED__
#define __CHECKSUMS_H_INCLUDED__

#include <wx/wx.h>

#include "wxmd5.h"
#include "wxsha1.h"

enum HashType
{
	HT_UNKNOWN = -1,
	HT_MD5,
	HT_SHA1,

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
};

#endif // __CHECKSUMBASE_H_INCLUDED__
