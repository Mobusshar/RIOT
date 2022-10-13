/*
 * Copyright (C) 2015 INRIA
 * Copyright (C) 2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     core_util
 *
 * @{
 * @file
 * @brief       POSIX.1-2008 compliant version of the assert macro
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      René Kijewski <rene.kijewski@fu-berlin.de>
 * @author      Martine Lenders <m.lenders@fu-berlin.de>
 */

#ifndef ASSERT_H
#define ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DOXYGEN
/**
 * @brief   Activate verbose output for @ref assert() when defined.
 *
 * Without this macro defined the @ref assert() macro will just print the
 * address of the code line the assertion failed in. With the macro defined
 * the macro will also print the file, the code line and the function this macro
 * failed in.
 *
 * To define just add it to your `CFLAGS` in your application's Makefile:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.mk}
 * CFLAGS += -DDEBUG_ASSERT_VERBOSE
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define DEBUG_ASSERT_VERBOSE
#endif

#ifndef RIOT_FILE_RELATIVE
#define RIOT_FILE_RELATIVE  (__FILE__)
#endif

/**
 * @def __NORETURN
 * @brief hidden (__) NORETURN definition
 * @internal
 *
 * Duplicating the definitions of kernel_defines.h as these are unsuitable for
 * system header files like the assert.h.
 * kernel_defines.h would define symbols that are not reserved.
 */
#ifndef __NORETURN
#ifdef __GNUC__
#define __NORETURN __attribute__((noreturn))
#else /*__GNUC__*/
#define __NORETURN
#endif /*__GNUC__*/
#endif /*__NORETURN*/

#ifdef NDEBUG
#define assert(ignore)((void)0)
#elif defined(DEBUG_ASSERT_VERBOSE)
/**
 * @brief   Function to handle failed assertion
 *
 * @note    This function was introduced for memory size optimization
 *
 * @warning this function **NEVER** returns!
 *
 * @param[in] file  The file name of the file the assertion failed in
 * @param[in] line  The code line of @p file the assertion failed in
 */
__NORETURN void _assert_failure(const char *file, unsigned line);
/**
 * @brief    abort the program if assertion is false
 *
 * If the macro NDEBUG was defined at the moment <assert.h> was last included,
 * the macro assert() generates no code, and hence does nothing at all.
 *
 * Otherwise, the macro assert() prints an error message to standard error and
 * terminates the application by calling core_panic().
 *
 * The purpose of this macro is to help programmers find bugs in their
 * programs.
 *
 * With @ref DEBUG_ASSERT_VERBOSE defined this will print also the file, the
 * line and the function this assertion failed in.
 *
 * If `NDEBUG` and @ref DEBUG_ASSERT_VERBOSE are not defined, a failed assertion
 * generates output similar to:
 *
 *     0x89abcdef
 *     *** RIOT kernel panic:
 *     FAILED ASSERTION.
 *
 *     ...
 *
 * Where 0x89abcdef is an address. This address can be used with tools like
 * `addr2line` (or e.g. `arm-none-eabi-addr2line` for ARM-based code), `objdump`,
 * or `gdb` (with the command `info line *(0x89abcdef)`) to identify the line
 * the assertion failed in.
 *
 * If the `backtrace` module is enabled (and implemented for architecture in use)
 * a backtrace will be printed in addition to the location of the failed assertion.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/assert.html
 */
#define assert(cond) ((cond) ? (void)0 :  _assert_failure(RIOT_FILE_RELATIVE, \
                                                          __LINE__))
#else /* DEBUG_ASSERT_VERBOSE */
__NORETURN void _assert_panic(void);
#define assert(cond) ((cond) ? (void)0 : _assert_panic())
#endif /* DEBUG_ASSERT_VERBOSE */

#if !defined __cplusplus
#if __STDC_VERSION__ >= 201112L
/**
 * @brief c11 static_assert() macro
 */
#define static_assert(...) _Static_assert(__VA_ARGS__)
#else
/**
 * @brief static_assert for c-version < c11
 *
 * Generates a division by zero compile error when cond is false
 */
#define static_assert(cond, ...) \
    { enum { static_assert_failed_on_div_by_0 = 1 / (!!(cond)) }; }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* ASSERT_H */
/** @} */
