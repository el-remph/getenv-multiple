Multiple getenv (single-pass)
=============================

Alright, I can explain. I see constructs all the time like

```c
	char * result, * confdir;
	if ((result = getenv("XDG_CONFIG_HOME")))
		confdir = asprintf("%s/%s", result, name);
	else if ((result = getenv("HOME")))
		confdir = asprintf("%s/.%s", result, name);
	else
		...
```

and it bugs me (aha), because this makes a whopping two passes over the
environment to perform a linear search when it could make just one. See
examples/ for more justification for this thing's existence.

The only distribution/installation files are are libgetenv_multiple.a and
[getenv_multiple.h][]; all documentation and full licence text is in the
latter. The documentation may very well be parseable with doxygen, I
haven't tried


Copyright
---------

&copy; 2024 The Remph <lhr@disroot.org>, under the BSD-2-Clause licence;
see the top of [getenv_multiple.h][] for the full licence text.

The file [alloca.h][] is from gnulib and is LGPL-2.1-or-later. It's only
used for `getenv_preferences()`, in the event that C99 or GNU C are
unavailable, so if for some reason you're really against encompassing
copyleft code, those are the only conditions under which that would
happen.


[getenv_multiple.h]: ./getenv_multiple.h
[alloca.h]: ./alloca.h
