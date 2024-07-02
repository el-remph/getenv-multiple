#include <stdio.h>	/* asprintf(3) */

#include "getenv_multiple.h"

const char * __attribute__((__malloc__))
get_confdir(void)
/* inspired by dillo dlib */
{
	static const char *restrict confdir = NULL;

	if (!confdir) {
		const char
			rootdir[]	= "/",
			name[]		= "foo",
			*const vars[]	= { "XDG_CONFIG_DIR", "HOME", "HOMEDRIVE", "HOMEPATH" },
			* vals[]	= { NULL, NULL, NULL, NULL };
		getenv_multiple(vars, vals, sizeof vars / sizeof *vars);
		confdir =
			vals[0] ?
				asprintf("%s/%s", vals[0], name)
			: vals[1] ?
				asprintf("%s/.config/%s", vals[1], name);
			: (vals[2] && vals[3]) ?
				asprintf("%s%s/_%s", vals[2], vals[3], name);
			:
				rootdir;

		if (confdir == NULL)
			perror("Can't into config directory");
		else if (confdir == rootdir)
			fputs("environment fucked\n", stderr);
		/* else no worries */
	}

	return confdir;
}
