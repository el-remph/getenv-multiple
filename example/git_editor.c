#ifdef TEST
#include <stdio.h>
#endif

#include "../getenv_multiple.h"

const char *
gitenv_editor(void)
{
	const char *const result =
		getenv_preferences("GIT_EDITOR", "VISUAL", "EDITOR", NULL);
	return result ? result : "ed"; /* the standard text editor! */
}

#ifdef TEST
int
main(void)
{
	puts(gitenv_editor());
	return 0;
}
#endif
