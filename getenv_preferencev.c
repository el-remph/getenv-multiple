#include <string.h>	/* strchr(3), strncmp(3) */
#include "getenv_multiple.h"

/* see corresponding notes in getenv_multiple.c */
extern const char *const * environ;

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
extern char *
getenv_preferencev(const char *const opts[])
{
	const char *const * envptr = environ;
	char * current_value = NULL;
	size_t current_rank = (size_t)-1;	/* ironically, should compare >= any
						 * index of opts */
	for (; *envptr; envptr++) {
		size_t i = 0;
		char *const equals = strchr(*envptr, '=');

		if (!equals)
			continue;

		for (; opts[i]; i++) {
			if (strncmp(opts[i], *envptr, equals - *envptr) == 0) {
				if (i == 0)
					return equals + 1;
				if (i <= current_rank)
					current_value = equals + 1,
					current_rank = i;
				break; /* assume the same string won't appear in opts twice */
			}
		}
	}

	return current_value;
}
