/******************************************************************************
 * Compiler attributes support.                                               *
 *                                                                            *
 * Purpose : Provides macros for utilizing compiler attributes.               *
 * Author  : Maxwell Powlison (bobdavelisafrank@protonmail.com)               *
 * License : This code is available under the GNU GPL v3.0. See `License.txt` *
 *           for more details.                                                *
 *                                                                            *
 ******************************************************************************/
#ifndef HDR_ATTR
#define HDR_ATTR

#define CC_ATTR(attr) __attribute__((attr))

/* Notes on Enums
 *   The use of `PACKED` and `MODE(...)` is valid for specifying widths of an
 *   enum. Use this to save on conversions.
 */

/******************************************************************************
 * Variable attributes.                                                       *
 ******************************************************************************/

/** ALIGN
 *
 * Makes sure that the given variable is algined to an x-byte boundary. Also
 * works with functions.
 */
#define ALIGN(x) CC_ATTR(aligned(x))



/** ALIGN_WARN_IFN
 *
 * Generates a compiler warning if a field of a struct is not aligned to the
 * given boundary.
 */
#define ALIGN_WARN_IFN(x) CC_ATTR(warn_if_not_aligned(x))



/** CLEANUP
 *
 * Sets the cleanup function, ran on the variable when the variable goes out of 
 * scope.
 */
#define CLEANUP(func) CC_ATTR(cleanup(func))



/** COMMON
 *
 * Sets a variable to be allocated in common storage (the BSS).
 */
#define COMMON CC_ATTR(common)



/** NOCOMMON
 *
 * Sets a variable to be explicitly not allocated in the BSS.
 */
#define NOCOMMON CC_ATTR(nocommon)



/** DEPRECATED
 *
 * Marks a variable as deprecated, causing it to generate a warning whenever it
 * is used. Also works with functions.
 */
#define DEPRECATED(msg) CC_ATTR(deprecated(msg))



/** MODE
 *
 * Sets the data type for the declaration, allowing the explicit setting of
 * type widths.
 */
#define MODE(m) CC_ATTR(mode(m))

/* Modes for explicit bit-counts.
 */
#define MODE_b8   CC_ATTR(mode(QI))
#define MODE_b16  CC_ATTR(mode(HI))
#define MODE_b32  CC_ATTR(mode(SI))
#define MODE_b64  CC_ATTR(mode(DI))
#define MODE_b128 CC_ATTR(mode(TI))

#define MODE_BYTE    CC_ATTR(mode(byte))
#define MODE_WORD    CC_ATTR(mode(word))
#define MODE_POINTER CC_ATTR(mode(pointer))



/** PACKED
 *
 * Sets a field in a struct (or a whole struct) to use the minimum possible
 * alignment. This is highly valuable for making direct representations of
 * hardware-defined structures.
 */
#define PACKED CC_ATTR(packed)



/** SECTION
 *
 * Puts the (global) variable or function into the explicitly titled section of
 * the executable.
 */
#define SECTION(sec_name_str) CC_ATTR(section(sec_name_str))



/** UNUSED
 *
 * Tells the C compiler that the variable is meant to be unused. That is, it
 * supressess warnings of unused variables. Also works with functions.
 */
#define UNUSED CC_ATTR(unused)



/** USED
 *
 * Tells the compiler to still generate a static variable even if there are
 * no references to it within the compilation unit. Also works with functions.
 */
#define USED CC_ATTR(used)



/** VISIBILITY
 *
 * Changes the linker visibility of the given variable (or function).
 */
#define VISIBILITY(type_str) CC_ATTR(visibility(type_str))


	
/******************************************************************************
 * Function attributes.                                                       *
 ******************************************************************************/

/** ALIAS
 *
 * Defines a function to be another name for a given symbol.
 */
#define ALIAS(symbol_str) CC_ATTR(alias(symbol_str))



/** COLD
 *
 * Tells the compiler that the function is less likely to be used, and as such
 * it will be optimized for size and other functions will be given higher
 * priority for locality.
 */
#define COLD CC_ATTR(cold)



/** HOT
 *
 * The opposite of COLD -- more speed optimization, and improved locality.
 */
#define HOT CC_ATTR(hot)



/** NONNULL
 *
 * Tells that the given argument indexes (starting at 1) cannot be NULL -- that
 * is, the compiler will generate warnings upon NULL arguments given to
 * functions with this attribute.
 */
#define NONNULL(arg_indices...) CC_ATTR(nonnull(arg_indices))


	
/** NONNULL_ALL
 *
 * Tells the compiler that all pointer arguments to a function must be non-NULL.
 */
#define NONNULL_ALL CC_ATTR(nonnull)



/** NONNULL_RETURN
 *
 * Tells the compiler that the pointer returned by a function will never be
 * NULL.
 */
#define NONNULL_RETURN CC_ATTR(returns_nonnull)



/** NORETURN
 *
 * Tells the compiler that the given function never returns.
 */
#define NORETURN CC_ATTR(noreturn)



/** WARN_UNUSED_RESULT
 *
 * Tells the compiler to generate warnings whenever the result of the function
 * call is not checked.
 */
#define WARN_UNUSED_RESULT CC_ATTR(warn_unused_result)



/** WEAK
 *
 * Sets the function's symbol to be a weak symbol, able to be replacable by
 * user code.
 */
#define WEAK CC_ATTR(weak)



#endif /* HDR_ATTR */

/* ----------------------------------- EOF ---------------------------------- */
