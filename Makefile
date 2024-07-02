# Build archives atomically (from the perspective of make -j, that is)
(%):%;
%.a: ; $(AR) rsv $@ $?

OBJS = getenv_multiple.o getenv_multiple_sorted.o getenv_preferences.o getenv_preferencev.o
PREFIX ?= /opt
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

# Prepend defaults to existing CFLAGS so they can be unset easily (eg.
# <make CFLAGS='-Wno-extra -std=gnu23'>)
CFLAGS := -Wall -Wextra -ansi $(CFLAGS)

.PHONY = all clean install
all: libgetenv_multiple.a
clean:
	rm -fv libgetenv_multiple.a alloca.h $(OBJS)
install: all
	install -D -m 644 -t $(LIBDIR) libgetenv_multiple.a
	install -D -m 644 -t $(INCLUDEDIR) getenv_multiple.h

libgetenv_multiple.a: libgetenv_multiple.a($(OBJS))
$(OBJS): getenv_multiple.h
getenv_preferences.o: alloca.h
alloca.h: alloca.in.h
	echo '#include <alloca.h>' | $(CC) $(CPPFLAGS) $(CFLAGS) -E - >/dev/null 2>&1 ; \
	sed "s/@HAVE_ALLOCA_H@/$$(( $$? == 0 ))/g" $<>$@
