#include <alloca.h>
#include <stdarg.h>

#include "getenv_multiple.h"

/**
 * Like getenv_preferencev(), but hairier. With C99, implemented via
 * variadic macro instead
 */
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

	argv = alloca(size);
	va_start(ap, begin);
	while ((argv[i++] = va_arg(ap, const char*)));
	va_end(ap);

	return getenv_preferencev(argv);
}
