/// About the MD5 algorithm used here :
///     Based on md5.h and md5.c reference implemantion of RFC 1321
///     Derived from the RSA Data Security, Inc.
///     MD5 Message-Digest Algorithm
///     Copyright (C) 1991 - 1992 RSA Data Security, Inc. Created 1991.
///     All rights reserved.

#ifndef __WXMD5_H_INCLUDED__
#define __WXMD5_H_INCLUDED__

#define wxMD5_BlockSize 64

#include <wx/wx.h>

class wxMD5
{
	public:
		wxMD5(const wxString& text=wxEmptyString);
		virtual ~wxMD5();
		void Update(const unsigned char *buf, wxUint32 length);
		wxMD5& Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		void Transform(const wxUint8 block[wxMD5_BlockSize]);
		static void Decode(wxUint32 output[], const wxUint8 input[], wxUint32 len);
		static void Encode(wxUint8 output[], const wxUint32 input[], wxUint32 len);

		bool m_bFinalized;
		wxUint8 m_uiBuffer[wxMD5_BlockSize]; // bytes that didn't fit in last 64 byte chunk
		wxUint32 m_uiCount[2];               // 64bit counter for number of bits (lo, hi)
		wxUint32 m_uiState[4];               // digest so far
		wxUint8 m_uiDigest[16];              // result

		// low level logic operations
		static inline wxUint32 F(wxUint32 x, wxUint32 y, wxUint32 z);
		static inline wxUint32 G(wxUint32 x, wxUint32 y, wxUint32 z);
		static inline wxUint32 H(wxUint32 x, wxUint32 y, wxUint32 z);
		static inline wxUint32 I(wxUint32 x, wxUint32 y, wxUint32 z);
		static inline wxUint32 rotate_left(wxUint32 x, int n);
		static inline void FF(wxUint32 &a, wxUint32 b, wxUint32 c, wxUint32 d, wxUint32 x, wxUint32 s, wxUint32 ac);
		static inline void GG(wxUint32 &a, wxUint32 b, wxUint32 c, wxUint32 d, wxUint32 x, wxUint32 s, wxUint32 ac);
		static inline void HH(wxUint32 &a, wxUint32 b, wxUint32 c, wxUint32 d, wxUint32 x, wxUint32 s, wxUint32 ac);
		static inline void II(wxUint32 &a, wxUint32 b, wxUint32 c, wxUint32 d, wxUint32 x, wxUint32 s, wxUint32 ac);
};

#endif // __WXMD5_H_INCLUDED__
