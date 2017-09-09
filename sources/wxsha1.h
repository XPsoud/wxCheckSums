/// About the SHA1 algorithm used here :
/// Original C++ Code
///   100% free public domain implementation of the SHA-1 algorithm
///   by Dominik Reichl <dominik.reichl@t-online.de>
///   Version 2.1 - 2012-06-19
///   Web: http://www.dominik-reichl.de/
/// wxWidgets version
///   Conversion by Xavier Perrissoud <x.psoud@gmail.com>

#ifndef __WXSHA1_H_INCLUDED__
#define __WXSHA1_H_INCLUDED__

#include <stdint.h>

#include <wx/wx.h>

// You can define the endian mode in your files without modifying the SHA-1
// source files. Just #define SHA1_LITTLE_ENDIAN or #define SHA1_BIG_ENDIAN
// in your files, before including the SHA1.h header file. If you don't
// define anything, the class defaults to little endian.
#if !defined(SHA1_LITTLE_ENDIAN) && !defined(SHA1_BIG_ENDIAN)
#define SHA1_LITTLE_ENDIAN
#endif

typedef union
{
	uint8_t c[64];
	uint32_t l[16];
} SHA1_WORKSPACE_BLOCK;

class wxSHA1
{
	public:
		wxSHA1(const wxString& text=wxEmptyString);
		~wxSHA1();
		void Update(const uint8_t* pbData, uint32_t uLen);
		void Finalize();
		wxString HexDigest() const;
	private:
		void Initialize();
		void Transform(uint32_t* pState, const uint8_t* pBuffer);

		bool m_bFinalized;
		uint32_t m_uiState[5];
		uint32_t m_uiCount[2];
		uint32_t m_reserved0[1]; // Memory alignment padding
		uint8_t m_uiBuffer[64];
		uint8_t m_uiDigest[20];
		uint32_t m_reserved1[3]; // Memory alignment padding
		uint8_t m_uiWorkspace[64];
		SHA1_WORKSPACE_BLOCK* m_block; // SHA1 pointer to the byte array above
};

#endif /* __WXSHA1_H_INCLUDED__ */
