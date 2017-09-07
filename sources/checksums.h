#ifndef __CHECKSUMS_H_INCLUDED__
#define __CHECKSUMS_H_INCLUDED__

#include <wx/wx.h>

#include "wxmd5.h"

enum HashType
{
	HT_UNKNOWN = -1,
	HT_MD5,

	HT_COUNT
};

class CheckSums
{
	public:
		CheckSums(const wxString& text=wxEmptyString);
		virtual ~CheckSums();
		wxString GetHexDigest(HashType type);
	protected:
	private:
		wxMD5 m_md5;
};

#endif // __CHECKSUMBASE_H_INCLUDED__
