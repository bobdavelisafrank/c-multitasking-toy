/******************************************************************************
 * Integer types and handling library.                                        *
 *                                                                            *
 * Authors:                                                                   *
 *   Maxwell Powlison (bobdavelisafrank@protonmail.com)                       *
 *                                                                            *
 * License:                                                                   *
 *   This code is available under the GNU GPL v3.0. See `License.txt` for     *
 *   more details.                                                            *
 ******************************************************************************/
#pragma once

#ifndef   NULL
#  define NULL ((void *) 0)
#endif

#ifndef   true
#  define true 1
#endif

#ifndef   false
#  define false 0
#endif

#include <std/c11.h>
#include <gcc/attr.h>
#include <gcc/builtin.h>

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

typedef MODE_b8   int i8;
typedef MODE_b16  int i16;
typedef MODE_b32  int i32;
typedef MODE_b64  int i64;
typedef MODE_b128 int i128;

typedef MODE_b8   unsigned int u8;
typedef MODE_b16  unsigned int u16;
typedef MODE_b32  unsigned int u32;
typedef MODE_b64  unsigned int u64;
typedef MODE_b128 unsigned int u128;

typedef MODE_POINTER int isize;
typedef MODE_POINTER unsigned int usize;

#if __STDC_VERSION__ >= 199901L
typedef _Bool bool;
#else
typedef u8 bool;
#endif

/******************************************************************************
 * Integer ranges.                                                            *
 ******************************************************************************/

#define MIN_u8 0
#define MAX_u8 0xFF
#define MIN_i8 (- MAX_i8)
#define MAX_i8 0x7F

#define MIN_u16 0
#define MAX_u16 0xFFFF
#define MIN_i16 (- MAX_u16)
#define MAX_i16 0x7FFF

#define MIN_u32 0
#define MAX_u32 0xFFFFFFFF
#define MIN_i32 (- MAX_u32)
#define MAX_i32 0x7FFFFFFF

#define MIN_u64 0
#define MAX_u64 0xFFFFFFFFFFFFFFFF
#define MIN_i64 (- MAX_u64)
#define MAX_i64 0x7FFFFFFFFFFFFFFF

/******************************************************************************
 * Testing integer sizes.                                                     *
 ******************************************************************************/

ASSERT_SIZE (i8, 1);
ASSERT_SIZE (u8, 1);

ASSERT_SIZE (i16, 2);
ASSERT_SIZE (u16, 2);

ASSERT_SIZE (i32, 4);
ASSERT_SIZE (u32, 4);

ASSERT_SIZE (i64, 8);
ASSERT_SIZE (u64, 8);

ASSERT_SIZE (i128, 16);
ASSERT_SIZE (u128, 16);

/******************************************************************************
 * Helper function-macros.                                                    *
 ******************************************************************************/

#define max(a, b)				\
	({					\
		typeof (a) _a = (a);		\
		typeof (b) _b = (b);		\
		_a > _b ? _a : _b;		\
	})

#define min(a, b)				\
	({					\
		typeof (a) _a = (a);		\
		typeof (b) _b = (b);		\
		_a < _b ? _a : _b;		\
	})

// Rounds `n` to the nearest multiple of `m`, rounding down or up.
#define floor(n, m)				\
	({					\
		typeof (n) _n = (n);		\
		typeof (m) _m = (m);		\
		_n - (_n % _m);			\
	})

#define ceil(n, m)				\
	({					\
		typeof (n) _n = (n);		\
		typeof (m) _m = (m);		\
		typeof (n) _rem = _n % _m;	\
		(_n - _rem) + _m * (_rem > 0);	\
	})

// Division with explicit rounding behavior.
#define div_floor(n, d)				\
	({					\
		typeof (n) _n = (n);		\
		typeof (d) _d = (d);		\
		_n / _d;			\
	})

#define div_ceil(n, d)				\
	({					\
		typeof (n) _n = (n);		\
		typeof (d) _d = (d);		\
		_n / _d + (_n % _d != 0);	\
	})

// Logarithm functions; these are on the intensive side.
#define log2_floor(x)				\
	({					\
		typeof (x) _x = (x);		\
		typeof (x) _log_x = 0;		\
						\
		while (_x > 1) {		\
			_x >>= 1;		\
			_log_x++;		\
		}				\
						\
		_log_x;				\
	})

#define log2_ceil(x)					\
	({						\
		typeof (x) _x = (x);			\
		typeof (x) _log_x = log2_floor (_x);	\
		typeof (x) _pow2 = 1 << _log_x;		\
		_log_x + (_x > _pow2);			\
	})

#define pow2(x)					\
	({					\
		typeof (x) _x = (x);		\
		1 << x;				\
	})

/* ----------------------------------- EOF ---------------------------------- */
