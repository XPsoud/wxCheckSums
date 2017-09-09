/// About the MD5 algorithm used here :
///     Based on md5.h and md5.c reference implemantion of RFC 1321
///     Derived from the RSA Data Security, Inc.
///     MD5 Message-Digest Algorithm
///     Copyright (C) 1991 - 1992 RSA Data Security, Inc. Created 1991.
///     All rights reserved.

#ifndef __WXMD5_H_INCLUDED__
#define __WXMD5_H_INCLUDED__

#include <stdint.h>

#include <wx/wx.h>

class wxMD5
{
	public:
		wxMD5(const wxString& text=wxEmptyString);
		virtual ~wxMD5();
		void Update(const unsigned char *buf, uint32_t length);
		wxMD5& Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		void Transform(const uint8_t block[64]);
		static void Decode(uint32_t output[], const uint8_t input[], uint32_t len);
		static void Encode(uint8_t output[], const uint32_t input[], uint32_t len);

		bool m_bFinalized;
		uint8_t m_uiBuffer[64];              // bytes that didn't fit in last 64 byte chunk
		uint32_t m_uiCount[2];               // 64bit counter for number of bits (lo, hi)
		uint32_t m_uiState[4];               // digest so far
		uint8_t m_uiDigest[16];              // result

		// low level logic operations
		static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z);
		static inline uint32_t rotate_left(uint32_t x, int n);
		static inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
		static inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
};

#endif // __WXMD5_H_INCLUDED__
