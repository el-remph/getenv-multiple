#include "getenv_multiple.h"

const char *
gitenv_editor(void)
{
	const char *const result =
		getenv_preferences("GIT_EDITOR", "VISUAL", "EDITOR", NULL);
	return result ? result : "vi";
}
