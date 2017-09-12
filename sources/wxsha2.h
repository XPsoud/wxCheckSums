/*
 * Updated to C++, zedwood.com 2012
 * Based on Olivier Gay's version
 * See Modified BSD License below:
 *
 * Conversion to wxWidgets by Xavier Perrissoud <x.psoud@gmail.com>
 *
 * FIPS 180-2 SHA-224/256/384/512 implementation
 * Issue date:  04/30/2005
 * http://www.ouah.org/ogay/sha2/
 *
 * Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __WXSHA2_H_INCLUDED__
#define __WXSHA2_H_INCLUDED__

#include <wx/wx.h>
#include <stdint.h>

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

class wxSHA256 : public wxSHA2
{
	public:
		wxSHA256(const wxString& text=wxEmptyString);
		virtual ~wxSHA256();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
		static const uint32_t DIGEST_SIZE = ( 256 / 8);
	protected:
		void Transform(const unsigned char *message, unsigned int block_nb);
		const static uint32_t sha256_k[];
		static const uint32_t SHA224_256_BLOCK_SIZE = (512/8);
		uint32_t m_tot_len;
		uint32_t m_len;
		unsigned char m_block[2*SHA224_256_BLOCK_SIZE];
		uint32_t m_h[8];
	private:
		void Initialize();
		uint8_t m_uiDigest[DIGEST_SIZE];
};


class wxSHA224 : public wxSHA256
{
	public:

		wxSHA224(const wxString& text=wxEmptyString);
		virtual ~wxSHA224();
		void Update(const unsigned char *message, unsigned int len);
		void Finalize();
		wxString HexDigest() const;
		static const uint32_t DIGEST_SIZE = ( 224 / 8);
	private:
		void Initialize();
		uint8_t m_uiDigest[DIGEST_SIZE];
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
		void Transform(const unsigned char *message, unsigned int block_nb);
		const static uint64_t sha512_k[];
		static const uint32_t SHA384_512_BLOCK_SIZE = (1024/8);
		unsigned int m_tot_len;
		unsigned int m_len;
		unsigned char m_block[2 * SHA384_512_BLOCK_SIZE];
		uint64_t m_h[8];
	private:
		void Initialize();
		static const uint32_t DIGEST_SIZE = ( 512 / 8);
		uint8_t m_uiDigest[DIGEST_SIZE];
};

class wxSHA384 : public wxSHA512
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
};

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA512_F1(x) (SHA2_ROTR(x, 28) ^ SHA2_ROTR(x, 34) ^ SHA2_ROTR(x, 39))
#define SHA512_F2(x) (SHA2_ROTR(x, 14) ^ SHA2_ROTR(x, 18) ^ SHA2_ROTR(x, 41))
#define SHA512_F3(x) (SHA2_ROTR(x,  1) ^ SHA2_ROTR(x,  8) ^ SHA2_SHFR(x,  7))
#define SHA512_F4(x) (SHA2_ROTR(x, 19) ^ SHA2_ROTR(x, 61) ^ SHA2_SHFR(x,  6))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
	*((str) + 3) = (uint8_t) ((x)      );       \
	*((str) + 2) = (uint8_t) ((x) >>  8);       \
	*((str) + 1) = (uint8_t) ((x) >> 16);       \
	*((str) + 0) = (uint8_t) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
	*(x) =   ((uint32_t) *((str) + 3)      )    \
		   | ((uint32_t) *((str) + 2) <<  8)    \
		   | ((uint32_t) *((str) + 1) << 16)    \
		   | ((uint32_t) *((str) + 0) << 24);   \
}
#define SHA2_UNPACK64(x, str)                 \
{                                             \
	*((str) + 7) = (uint8_t) ((x)      );       \
	*((str) + 6) = (uint8_t) ((x) >>  8);       \
	*((str) + 5) = (uint8_t) ((x) >> 16);       \
	*((str) + 4) = (uint8_t) ((x) >> 24);       \
	*((str) + 3) = (uint8_t) ((x) >> 32);       \
	*((str) + 2) = (uint8_t) ((x) >> 40);       \
	*((str) + 1) = (uint8_t) ((x) >> 48);       \
	*((str) + 0) = (uint8_t) ((x) >> 56);       \
}
#define SHA2_PACK64(str, x)                   \
{                                             \
	*(x) =   ((uint64_t) *((str) + 7)      )    \
		   | ((uint64_t) *((str) + 6) <<  8)    \
		   | ((uint64_t) *((str) + 5) << 16)    \
		   | ((uint64_t) *((str) + 4) << 24)    \
		   | ((uint64_t) *((str) + 3) << 32)    \
		   | ((uint64_t) *((str) + 2) << 40)    \
		   | ((uint64_t) *((str) + 1) << 48)    \
		   | ((uint64_t) *((str) + 0) << 56);   \
}

#endif // __WXSHA2_H_INCLUDED__
