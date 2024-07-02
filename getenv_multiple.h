#ifndef GETENV_MULTIPLE_H
#define GETENV_MULTIPLE_H

#include <stddef.h>	/* size_t */

#ifdef __cplusplus
#  define C "C"
#else
#  define C
#endif /* C++ */

extern C void
	getenv_multiple(const char *const in[], const char * out[], size_t size)
		__attribute__((	__access__(__read_only__, 1, 3),
				__access__(__write_only__, 2, 3))),
	getenv_multiple_sorted(const char *const in[], const char * out[], size_t size)
		__attribute__((	__access__(__read_only__, 1, 3),
				__access__(__write_only__, 2, 3)));

extern C char
	*getenv_preferencev(const char *const opts[]),
	*getenv_preferences_(const char*, ...) __attribute__((sentinel));

#if __STDC_VERSION__ >= 199900L
#  define getenv_preferences(...)	getenv_preferencev((char**){__VA_ARGS__})
#elif defined __GNUC__ && !defined __STRICT_ANSI__
#  define getenv_preferences(args...)	getenv_preferencev((char**){args})
#else
#  define getenv_preferences getenv_preferences_
#endif /* C99 */

#endif /* GETENV_MULTIPLE_H */
