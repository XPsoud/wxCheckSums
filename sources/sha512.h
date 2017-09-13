/* Declarations of functions and data types used for SHA512 and SHA384 sum
   library functions.
   Copyright (C) 2005-2006, 2008-2017 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef SHA512_H
# define SHA512_H 1

# include <stdio.h>
#include <stdint.h>

/* Return X rotated left by N bits, where 0 < N < 64.  */
#define u64rol(x, n) u64or (u64shl (x, n), u64shr (x, 64 - n))

typedef uint64_t u64;
# define u64hilo(hi, lo) ((u64) (((u64) (hi) << 32) + (lo)))
# define u64init(hi, lo) u64hilo (hi, lo)
# define u64lo(x) ((u64) (x))
# define u64size(x) u64lo (x)
# define u64lt(x, y) ((x) < (y))
# define u64and(x, y) ((x) & (y))
# define u64or(x, y) ((x) | (y))
# define u64xor(x, y) ((x) ^ (y))
# define u64plus(x, y) ((x) + (y))
# define u64shl(x, n) ((x) << (n))
# define u64shr(x, n) ((x) >> (n))

# ifdef __cplusplus
extern "C" {
# endif

enum { SHA384_DIGEST_SIZE = 384 / 8 };
enum { SHA512_DIGEST_SIZE = 512 / 8 };

/* Structure to save state of computation between the single steps.  */
struct sha512_ctx
{
  u64 state[8];

  u64 total[2];
  size_t buflen;  /* ≥ 0, ≤ 256 */
  u64 buffer[32]; /* 256 bytes; the first buflen bytes are in use */
};

/* Initialize structure containing state of computation. */
extern void sha512_init_ctx (struct sha512_ctx *ctx);
extern void sha384_init_ctx (struct sha512_ctx *ctx);

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is necessary that LEN is a multiple of 128!!! */
extern void sha512_process_block (const void *buffer, size_t len,
                                  struct sha512_ctx *ctx);

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is NOT required that LEN is a multiple of 128.  */
extern void sha512_process_bytes (const void *buffer, size_t len,
                                  struct sha512_ctx *ctx);

/* Process the remaining bytes in the buffer and put result from CTX
   in first 64 (48) bytes following RESBUF.  The result is always in little
   endian byte order, so that a byte-wise output yields to the wanted
   ASCII representation of the message digest.  */
extern void *sha512_finish_ctx (struct sha512_ctx *ctx, void *resbuf);
extern void *sha384_finish_ctx (struct sha512_ctx *ctx, void *resbuf);


/* Put result from CTX in first 64 (48) bytes following RESBUF.  The result is
   always in little endian byte order, so that a byte-wise output yields
   to the wanted ASCII representation of the message digest.

   IMPORTANT: On some systems it is required that RESBUF is correctly
   aligned for a 32 bits value.  */
extern void *sha512_read_ctx (const struct sha512_ctx *ctx, void *resbuf);
extern void *sha384_read_ctx (const struct sha512_ctx *ctx, void *resbuf);

# ifdef __cplusplus
}
# endif

#endif
