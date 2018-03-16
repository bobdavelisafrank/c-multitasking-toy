/******************************************************************************
 * Support for GCC compiler built-ins.                                        *
 *                                                                            *
 * Authors:                                                                   *
 *   Maxwell Powlison (bobdavelisafrank@protonmail.com)                       *
 *                                                                            *
 * License:                                                                   *
 *   This code is available under the GNU GPL v3.0. See `License.txt` for     *
 *   more details.                                                            *
 *                                                                            *
 ******************************************************************************/
#pragma once

/******************************************************************************
 * General.                                                                   *
 ******************************************************************************/

#define typeof __typeof__

// Tests if two types are the same (ignoring top-level qualifiers).
#define types_compatible(t1, t2) __builtin_types_compatible_p(t1, t2)

// Alternate to `?:` without side-effects or type promotion.
#define choose_expr(const_exp, exp1, exp2) __builtin_choose_expr(exp1, exp2)

// Tells if the given value is a constant.
#define is_constant(exp) __builtin_constant_p(exp)

// Function which specifies an unreachable endpoint of a function, for stopping
// compiler warning of non-returning functions and such. Needs `()`'s, as this
// is a function.
#define unreachable __builtin_unreachable

// Find first set-bit. Returns the index of the bit + 1, or 0 if there is no
// set bit.
#define int_ffs(x) __builtin_ffs(x)
#define long_ffs(x) __builtin_ffsl(x)

// Count leading/trailing zeros. Undefined if x is 0.
#define int_clz(x)  __builtin_clz(x)
#define int_ctz(x)  __builtin_ctz(x)
#define long_clz(x) __builtin_clzl(x)
#define long_ctz(x) __builtin_ctzl(x)

// Count leading redundant sign bits.
#define int_clrsb(x)  __builtin_clrsb(x)
#define long_clrsb(x) __builtin_clrsbl(x)

// Returns the number of 1-bits.
#define int_popcount(x)  __builtin_popcount(x)
#define long_popcount(x) __builtin_popcountl(x)

// Returns the parity, popcount % 2.
#define int_parity(x)  __builtin_parity(x)
#define long_parity(x) __builtin_parityl(x)

// Reverse the order of bytes in a word.
#define bswap16(x) __builtin_bswap16(x)
#define bswap32(x) __builtin_bswap32(x)
#define bswap64(x) __builtin_bswap64(x)

/******************************************************************************
 * Arithmetic.                                                                *
 ******************************************************************************/

// Arithmetic with overflow-checking. Booleans are returned indicating overflow.
#define add(a, b, res_ptr) __builtin_add_overflow(a, b, res_ptr)
#define sub(a, b, res_ptr) __builtin_sub_overflow(a, b, res_ptr)
#define mul(a, b, res_ptr) __builtin_mul_overflow(a, b, res_ptr)

// Checks if overflow will occur with an arithmetic operation.
#define can_add(a, b) __builtin_add_overflow_p(a, b, typeof ((a) + (b)) 0)
#define can_sub(a, b) __builtin_sub_overflow_p(a, b, typeof ((a) + (b)) 0)
#define can_mul(a, b) __builtin_mul_overflow_p(a, b, typeof ((a) + (b)) 0)

/******************************************************************************
 * Object-size checking.                                                      *
 ******************************************************************************/

#define object_size(ptr, obj_type) __builtin_object_size(ptr, obj_type)

/******************************************************************************
 * Pointer bounds checker.                                                    *
 ******************************************************************************/

/* Note -- I haven't played around with the pointer bounds checker, and I can't
 * find much more documentation on it other than the fact it exists. I'm not
 * sure if it enables better static analysis, or just works as an optimization
 * hint.
 *
 * The flags for controlling the feature are:
 *   -fcheck-pointer-bounds
 *   -fno-check-pointer-bounds
 *
 * When the feature is disabled, functions which create pointers return their
 * first arguments, and other associated function-calls are ignored.
 * 
 * The source of this is the GCC documentation:
 *   gcc.gnu.org/onlinedocs/gcc/Pointer-Bounds-Checker-builtins.html
 */

// Creates a new pointer associated with bounds [q, q + size).
#define ptr_bound(q, size) __builtin__bnd_set_ptr_bounds(q, size)

// Binds pointer with interesction of bounds [p, p + size) and q's bounds.
#define ptr_narrow(p, q, size) __builtin__bnd_narrow_ptr_bounds(p, q, size)

// Copies a pointer and its bounds.
#define ptr_copy(q, r) __builtin__bnd_copy_ptr_bounds(q, r)

// Creates a pointer with either full-range bounds or no bounds.
#define ptr_init(q)      __builtin__bnd_init_ptr_bounds(q)
#define ptr_init_null(q) __builtin__bnd_null_ptr_bounds(q)

// Stores the bounds associated with a given pointer into the bounds-table.
#define ptr_store_bound(ptr_addr, ptr_val) \
	__builtin__bnd_store_ptr_bounds(ptr_addr, ptr_val)

// Checks if a pointer is within its associated bounds.
#define ptr_check_lower(q) __builtin__bnd_chk_ptr_lbounds(q)
#define ptr_check_upper(q) __builtin__bnd_chk_ptr_ubounds(q)
#define ptr_check_bound(q) __builtin__bnd_chk_ptr_bounds(q)

// Gets the pointer's bounds.
#define ptr_lower(q) __builtin__bnd_get_ptr_lbound(q)
#define ptr_upper(q) __builtin__bnd_get_ptr_ubound(q)

/******************************************************************************
 * Memory operations.                                                         *
 ******************************************************************************/

#define memcpy(dest, src, num) __builtin_memcpy(dest, src, num)
#define memcmp(s1, s2, num)    __builtin_memcmp(dest, src, num)
#define memset(s, c, num)      __builtin_memset(dest, src, num)

/*----------------------------------------------------------------------------*
 * Operations on NUL-terminated strings.                                      *
 *----------------------------------------------------------------------------*/

#define stpcpy(dest, src)        __builtin_stpcpy(dest, src)
#define stpncpy(dest, src, num)  __builtin_stpncpy(dest, src, num)
#define strcpy(dest, src)        __builtin_strcpy(dest, src)
#define strncpy(dest, src, num)  __builtin_strncpy(dest, src, num)

#define strcmp(s1, s2)           __builtin_strcmp(s1, s2)
#define strncmp(s1, s2, num)     __builtin_strcmp(s1, s2, num)
#define strcasecmp(s1, s2)       __builtin_strcasecmp(s1, s2)
#define strncasecmp(s1, s2, num) __builtin_strcasecmp(s1, s2, num)

#define strcat(dest, src)        __builtin_strcat(dest, src)
#define strncat(dest, src, num)  __builtin_strncat(dest, src, num)

#define strchr(s, c)             __builtin_strchr(s, c)
#define strrchr(s, c)            __builtin_strrchr(s, c)

#define strpbrk(s, accept)       __builtin_strpbrk(s, accept)
#define strspn(s, accept)        __builtin_strspn(s, accept)
#define strcspn(s, reject)       __builtin_strcspn(s, reject)

#define strstr(haystack, needle) __builtin_strstr(haystack, needle)

#define strlen(s)                __builtin_strlen(s)

// Operations on characters.
#define isalnum(c) __builtin_isalnum(c)
#define isalpha(c) __builtin_isalpha(c)
#define iscntrl(c) __builtin_iscntrl(c)
#define isdigit(c) __builtin_isdigit(c)
#define isgraph(c) __builtin_isgraph(c)
#define islower(c) __builtin_islower(c)
#define isprint(c) __builtin_isprint(c)
#define ispunct(c) __builtin_ispunct(c)
#define isspace(c) __builtin_isspace(c)
#define isupper(c) __builtin_isupper(c)

#define isxdigit(c) __builtin_isxdigit(c)

#define tolower(c) __builtin_tolower(c)
#define toupper(c) __builtin_toupper(c)

/* ----------------------------------- EOF ---------------------------------- */
