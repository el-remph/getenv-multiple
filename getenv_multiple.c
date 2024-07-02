#include <string.h>	/* strchr(3), strncmp(3) */
#include "getenv_multiple.h"

/* we declare this as const for race monitoring purposes, to mean that we
   won't modify the environment, just read it */
extern const char *const * environ;

#if !1
	/* example */
#define N (sizeof env_vars / sizeof *env_vars)
	const char
		*const env_vars[] = { "ITERM_SESSION_ID", "TERM" },
		* env_vals[N] = { NULL };
	getenv_multiple(env_vars, env_vals, N);
#endif

extern void __attribute__((access(read_only, 1, 3), access(write_only, 2, 3)))
getenv_multiple(const char *const in[], const char * out[], size_t size)
{
	const char *const * envptr = environ;
	for (; *envptr; envptr++) {
		size_t i = 0;
		const char *const equals = strchr(*envptr, '=');

		if (!equals)
			continue;

		for (; i < size; i++) {
			if (strncmp(in[i], *envptr, equals - *envptr) == 0) {
				out[i] = equals + 1;
				break;
			}
		}
	}
}
