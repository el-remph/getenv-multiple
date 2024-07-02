/* Copyright (C) 2024, the Remph; all rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice in the documentation and/or other materials provided with
      the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef GETENV_MULTIPLE_H
#define GETENV_MULTIPLE_H

#include <stddef.h>	/* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Searches the environment for variables matching any of `in', and writes
 * their values to `out'
 *
 * `in' and `out' are string vectors, each `size' elements long. The value
 * of in[n], if found, will be written to out[n], so `out' MUST be at least
 * as long as `in'. If a string in `in' is not found, its corresponding
 * entry in `out' will be left untouched. If you want to see which
 * variables were not found, ensure every pointer in `out' is initialised
 * to NULL. Beware that this function will not initialise `out' for you, so
 * if out[n] is uninitialised and in[n] is not found, the value of out[n]
 * remains undefined. Note also that if `in' contains the same string more
 * than once, only the first one will be respected
 */
void getenv_multiple(const char *const in[], const char * out[], size_t size)
	__attribute__((	__access__(__read_only__, 1, 3),
			__access__(__write_only__, 2, 3)));

/**
 * This version uses bsearch(3) to search `in' for a string matching the
 * environment
 *
 * This should be faster than getenv_multiple(), especially when `in' is
 * large, but note that `in' MUST be sorted as by strcmp(3). If `in'
 * contains duplicate strings, the entry in `out' that may be written to is
 * undefined, so `in' should really not have duplicate strings. Otherwise,
 * everything in getenv_multiple() applies here also
 *
 * @param size	Size of both `in' and `out'
 * @see	getenv_multple()
 */
void getenv_multiple_sorted(const char *const in[], const char * out[], size_t size)
	__attribute__((	__access__(__read_only__, 1, 3),
			__access__(__write_only__, 2, 3)));

/**
 * Searches the environment for a variable that appears in opts, preferring
 * the leftmost entry in opts
 *
 * Basically
 *	result = getenv_preference((char**){"FOO", "BAR", "MUNG", NULL});
 * is a bit like
 *	(result = getenv("FOO")) || (result = getenv("BAR")) || (result = getenv("MUNG"))
 * but less mank, and it only performs one pass over the environment. It
 * should still short-circuit if "FOO" is found
 *
 * @param opts is a NULL-terminated array of NUL-terminated strings
 *
 * @returns a pointer to the value of the leftmost string in `opts' that
 * corresponds to an existing environment variable, or NULL if no string in
 * opts is found in the environment
 */
char *getenv_preferencev(const char *const opts[]);

/**
 * Like getenv_preferencev(), but hairier. With C99 or GNU C, implemented
 * via variadic macro instead
 */
char *getenv_preferences_(const char*, ...) __attribute__((sentinel));

#ifdef __cplusplus
}
#  define CHAR_PTR_PTR
#else
#  define CHAR_PTR_PTR (char**)
#endif

#if __STDC_VERSION__ >= 199900L
#  define getenv_preferences(...)	getenv_preferencev(CHAR_PTR_PTR{__VA_ARGS__})
#elif defined __GNUC__ && !defined __STRICT_ANSI__
#  define getenv_preferences(args...)	getenv_preferencev(CHAR_PTR_PTR{args})
#else
#  define getenv_preferences getenv_preferences_
#endif /* C99 */

#endif /* GETENV_MULTIPLE_H */
