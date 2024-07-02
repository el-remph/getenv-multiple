#include "getenv_multiple.h"

#include <stdlib.h>	/* bsearch(3) */
#include <string.h>	/* strchr(3), strncmp(3) */

extern const char *const * environ; /* see notes in getenv_multiple.c */

/* for bsearch(3) */
struct env_var {
	const char * str, * equals;
};
static int
envvar_name_cmp(const void * a, const void * b)
{
	const struct env_var * search_key = a;
	return strncmp(search_key->str, *(char*const*)b,
			search_key->equals - search_key->str);
}

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
extern void __attribute__((access(read_only, 1, 3), access(write_only, 2, 3)))
getenv_multiple_sorted(const char *const in[], const char * out[], size_t size)
{
	const char *const * envptr = environ;
	for (; *envptr; envptr++) {
		const struct env_var search_key = { *envptr, strchr(*envptr, '=') };
		const char *const * result;

		if (!search_key.equals)
			continue;

		if ((result = bsearch(&search_key, in, sizeof *in, size, envvar_name_cmp)))
			out[result - in] = search_key.equals + 1;
	}
}
