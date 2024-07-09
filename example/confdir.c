#define _GNU_SOURCE	/* asprintf(3) */
#include <stdio.h>	/* asprintf(3) */

#include "../getenv_multiple.h"

const char * __attribute__((__malloc__))
get_confdir(void)
/* inspired by dillo dlib */
{
	static char
		rootdir[] = "/",
		* confdir = NULL;

	if (!confdir) {
		const char
			name[]		= "foo",
			*const vars[]	= { "XDG_CONFIG_DIR", "HOME", "HOMEDRIVE", "HOMEPATH" },
			* vals[]	= { NULL, NULL, NULL, NULL };
		getenv_multiple(vars, vals, sizeof vars / sizeof *vars);
		if (vals[0])
			asprintf(&confdir, "%s/%s", vals[0], name);
		else if (vals[1])
			asprintf(&confdir, "%s/.config/%s", vals[1], name);
		else if (vals[2] && vals[3])
			asprintf(&confdir, "%s%s/_%s", vals[2], vals[3], name);
		else
			confdir = rootdir;

		if (confdir == NULL)
			perror("Can't into config directory");
		else if (confdir == rootdir)
			fputs("environment fucked\n", stderr);
		/* else no worries */
	}

	return confdir;
}

#ifdef TEST
int
main(void)
{
	puts(get_confdir());
	return 0;
}
#endif
