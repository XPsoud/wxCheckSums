/// About the SHA1 algorithm used here :
/// Original C++ Code
///   100% free public domain implementation of the SHA-1 algorithm
///   by Dominik Reichl <dominik.reichl@t-online.de>
///   Version 2.1 - 2012-06-19
///   Web: http://www.dominik-reichl.de/
/// wxWidgets version
///   Conversion by Xavier Perrissoud <x.psoud@gmail.com>

#include "wxsha1.h"

// Rotate p_val32 by p_nBits bits to the left
#define ROL32(p_val32,p_nBits) (((p_val32)<<(p_nBits))|((p_val32)>>(32-(p_nBits))))

#ifdef SHA1_LITTLE_ENDIAN
#define SHABLK0(i) (m_block->l[i] = \
	(ROL32(m_block->l[i],24) & 0xFF00FF00) | (ROL32(m_block->l[i],8) & 0x00FF00FF))
#else
#define SHABLK0(i) (m_block->l[i])
#endif

#define SHABLK(i) (m_block->l[i&15] = ROL32(m_block->l[(i+13)&15] ^ \
	m_block->l[(i+8)&15] ^ m_block->l[(i+2)&15] ^ m_block->l[i&15],1))

// SHA-1 rounds
#define S_R0(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK0(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R1(v,w,x,y,z,i) {z+=((w&(x^y))^y)+SHABLK(i)+0x5A827999+ROL32(v,5);w=ROL32(w,30);}
#define S_R2(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0x6ED9EBA1+ROL32(v,5);w=ROL32(w,30);}
#define S_R3(v,w,x,y,z,i) {z+=(((w|x)&y)|(w&x))+SHABLK(i)+0x8F1BBCDC+ROL32(v,5);w=ROL32(w,30);}
#define S_R4(v,w,x,y,z,i) {z+=(w^x^y)+SHABLK(i)+0xCA62C1D6+ROL32(v,5);w=ROL32(w,30);}

wxSHA1::wxSHA1(const wxString& text)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxSHA1\" object\n"));
#endif // __WXDEBUG__
	Initialize();
	if (!text.IsEmpty())
	{
		Update(text.c_str(), text.length());
		Finalize();
	}
}

wxSHA1::~wxSHA1()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxSHA1\" object\n"));
#endif // __WXDEBUG__
}

void wxSHA1::Initialize()
{
	m_block = (SHA1_WORKSPACE_BLOCK*)m_uiWorkspace;
	// SHA1 initialization constants
	m_uiState[0] = 0x67452301;
	m_uiState[1] = 0xEFCDAB89;
	m_uiState[2] = 0x98BADCFE;
	m_uiState[3] = 0x10325476;
	m_uiState[4] = 0xC3D2E1F0;

	m_uiCount[0] = 0;
	m_uiCount[1] = 0;
}

void wxSHA1::Transform(uint32_t* pState, const uint8_t* pBuffer)
{
	uint32_t a = pState[0], b = pState[1], c = pState[2], d = pState[3], e = pState[4];

	memcpy(m_block, pBuffer, 64);

	// 4 rounds of 20 operations each, loop unrolled
	S_R0(a,b,c,d,e, 0); S_R0(e,a,b,c,d, 1); S_R0(d,e,a,b,c, 2); S_R0(c,d,e,a,b, 3);
	S_R0(b,c,d,e,a, 4); S_R0(a,b,c,d,e, 5); S_R0(e,a,b,c,d, 6); S_R0(d,e,a,b,c, 7);
	S_R0(c,d,e,a,b, 8); S_R0(b,c,d,e,a, 9); S_R0(a,b,c,d,e,10); S_R0(e,a,b,c,d,11);
	S_R0(d,e,a,b,c,12); S_R0(c,d,e,a,b,13); S_R0(b,c,d,e,a,14); S_R0(a,b,c,d,e,15);
	S_R1(e,a,b,c,d,16); S_R1(d,e,a,b,c,17); S_R1(c,d,e,a,b,18); S_R1(b,c,d,e,a,19);
	S_R2(a,b,c,d,e,20); S_R2(e,a,b,c,d,21); S_R2(d,e,a,b,c,22); S_R2(c,d,e,a,b,23);
	S_R2(b,c,d,e,a,24); S_R2(a,b,c,d,e,25); S_R2(e,a,b,c,d,26); S_R2(d,e,a,b,c,27);
	S_R2(c,d,e,a,b,28); S_R2(b,c,d,e,a,29); S_R2(a,b,c,d,e,30); S_R2(e,a,b,c,d,31);
	S_R2(d,e,a,b,c,32); S_R2(c,d,e,a,b,33); S_R2(b,c,d,e,a,34); S_R2(a,b,c,d,e,35);
	S_R2(e,a,b,c,d,36); S_R2(d,e,a,b,c,37); S_R2(c,d,e,a,b,38); S_R2(b,c,d,e,a,39);
	S_R3(a,b,c,d,e,40); S_R3(e,a,b,c,d,41); S_R3(d,e,a,b,c,42); S_R3(c,d,e,a,b,43);
	S_R3(b,c,d,e,a,44); S_R3(a,b,c,d,e,45); S_R3(e,a,b,c,d,46); S_R3(d,e,a,b,c,47);
	S_R3(c,d,e,a,b,48); S_R3(b,c,d,e,a,49); S_R3(a,b,c,d,e,50); S_R3(e,a,b,c,d,51);
	S_R3(d,e,a,b,c,52); S_R3(c,d,e,a,b,53); S_R3(b,c,d,e,a,54); S_R3(a,b,c,d,e,55);
	S_R3(e,a,b,c,d,56); S_R3(d,e,a,b,c,57); S_R3(c,d,e,a,b,58); S_R3(b,c,d,e,a,59);
	S_R4(a,b,c,d,e,60); S_R4(e,a,b,c,d,61); S_R4(d,e,a,b,c,62); S_R4(c,d,e,a,b,63);
	S_R4(b,c,d,e,a,64); S_R4(a,b,c,d,e,65); S_R4(e,a,b,c,d,66); S_R4(d,e,a,b,c,67);
	S_R4(c,d,e,a,b,68); S_R4(b,c,d,e,a,69); S_R4(a,b,c,d,e,70); S_R4(e,a,b,c,d,71);
	S_R4(d,e,a,b,c,72); S_R4(c,d,e,a,b,73); S_R4(b,c,d,e,a,74); S_R4(a,b,c,d,e,75);
	S_R4(e,a,b,c,d,76); S_R4(d,e,a,b,c,77); S_R4(c,d,e,a,b,78); S_R4(b,c,d,e,a,79);

	// Add the working vars back into state
	pState[0] += a;
	pState[1] += b;
	pState[2] += c;
	pState[3] += d;
	pState[4] += e;
}

void wxSHA1::Update(const uint8_t* pbData, uint32_t uLen)
{
	uint32_t j = ((m_uiCount[0] >> 3) & 0x3F);

	if((m_uiCount[0] += (uLen << 3)) < (uLen << 3))
		++m_uiCount[1]; // Overflow

	m_uiCount[1] += (uLen >> 29);

	uint32_t i;
	if((j + uLen) > 63)
	{
		i = 64 - j;
		memcpy(&m_uiBuffer[j], pbData, i);
		Transform(m_uiState, m_uiBuffer);

		for( ; (i + 63) < uLen; i += 64)
			Transform(m_uiState, &pbData[i]);

		j = 0;
	}
	else i = 0;

	if((uLen - i) != 0)
		memcpy(&m_uiBuffer[j], &pbData[i], uLen - i);
}

void wxSHA1::Finalize()
{
	uint32_t i;

	uint8_t pbFinalCount[8];
	for(i = 0; i < 8; ++i)
		pbFinalCount[i] = static_cast<uint8_t>((m_uiCount[((i >= 4) ? 0 : 1)] >>
			((3 - (i & 3)) * 8) ) & 0xFF); // Endian independent

	Update((uint8_t*)"\200", 1);

	while((m_uiCount[0] & 504) != 448)
		Update((uint8_t*)"\0", 1);

	Update(pbFinalCount, 8); // Cause a Transform()

	for(i = 0; i < 20; ++i)
		m_uiDigest[i] = static_cast<uint8_t>((m_uiState[i >> 2] >> ((3 -
			(i & 3)) * 8)) & 0xFF);

	m_bFinalized=true;
}

wxString wxSHA1::HexDigest() const
{
	if (!m_bFinalized)
		return wxEmptyString;

	wxString sResult=wxEmptyString;
	for (int i=0; i<20; i++)
		sResult << wxString::Format(_T("%02x"), m_uiDigest[i]);

	return sResult;
}
