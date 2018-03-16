/******************************************************************************
 * C11 definitions.                                                           *
 *                                                                            *
 * Purpose : Provides definitions for making use of ISO C11 features.         *
 * Author  : Maxwell Powlison (bobdavelisafrank@protonmail.com)               *
 * License : This code is available under the GNU GPL v3.0. See `License.txt` *
 *           for more details.                                                *
 *                                                                            *
 ******************************************************************************/
#ifndef HDR_C11
#define HDR_C11

/* This file is really more of a formality, currently just renaming the C11
 * identifiers with a more standard style.
 */
#if __STDC_VERSION__ >= 201112L

#  ifndef   generic
#    define generic _Generic
#  endif

#  ifndef   noreturn
#    define noreturn _Noreturn
#  endif

#  ifndef   static_assert
#    define static_assert _Static_assert
#  endif

#  ifndef   alignas
#    define alignas _Alignas
#  endif

#  ifndef   alignof
#    define alignof _Alignof
#  endif

#else

#  ifndef   static_assert
#    warning "Static assertions are not being checked."
#    define static_assert(...)
#  endif

#  ifndef   noreturn
#    define noreturn
#  endif

#endif

/* Checks the size of the type at compile-time, throwing an error if it is 
 * incorrect.
 *
 * Current problems with this is that it doesn't state the actual size of the
 * type, needing one to check the size externally.
 */
#define ASSERT_SIZE(type, bytes)					\
	static_assert (sizeof (type) == bytes,				\
		       "Bad size for " #type " (should be " #bytes ")"	\
		)

#endif /* HDR_C11 */

/* ----------------------------------- EOF ---------------------------------- */
