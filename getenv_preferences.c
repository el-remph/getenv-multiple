#include <stdarg.h>
#include "alloca.h"
#include "getenv_multiple.h"

#ifdef HAVE_ALLOCA
#  define ALLOCATE alloca
#else
#  include <stdlib.h>	/* malloc(3), free(3) */
#  define ALLOCATE malloc
#endif

extern char *
getenv_preferences_(const char *begin, ...)
/*
 * Justification: look, I'm sure a sensible system would allow me to just
 * getenv_preferencev(&begin), but for portability's sake we've got to copy
 * entries from a va_list -- when that's likely what va_start would do in
 * the first place on a system where that mattered. It's exactly the kind
 * of pattern I hate, allocating a dozen buffers and copying the same data
 * from one to another just to avoid raw memory access. Just use the
 * original buffer!
 *
 * Anyway, I just guess (hope) that a user won't pass enough arguments to
 * fill more than half stack size
 */
{
	va_list ap;
	const char ** argv;
	size_t i = 0, size = 0;

	va_start(ap, begin);
	while (va_arg(ap, const char*))
		size++;
	va_end(ap);

	argv = ALLOCATE(size);
	va_start(ap, begin);
	while ((argv[i++] = va_arg(ap, const char*)));
	va_end(ap);

#if HAVE_ALLOCA
	return getenv_preferencev(argv);
#else
	{
		char *const result = getenv_preferencev(argv);
		free(argv);
		return result;
	}
#endif
}
