# Build archives atomically (from the perspective of make -j, that is)
(%):%;
%.a: ; $(AR) rsv $@ $?

OBJS = getenv_multiple.o getenv_multiple_sorted.o getenv_preferences.o getenv_preferencev.o
PREFIX ?= /opt
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

CFLAGS = -Wall -Wextra -std=c89 # more portable than -ansi

.PHONY = all clean install test
all: libgetenv_multiple.a
clean:
	rm -fv libgetenv_multiple.a alloca.h $(OBJS) example/a.out
install: all
	install -D -m 644 -t $(LIBDIR) libgetenv_multiple.a
	install -D -m 644 -t $(INCLUDEDIR) getenv_multiple.h
test: libgetenv_multiple.a
	$(MAKE) -j1 -C example CFLAGS+=-std=c89
	$(MAKE) -j1 -C example CFLAGS+=-std=gnu89
	$(MAKE) -j1 -C example CFLAGS+=-std=c11
# Strictly one job^, otherwise there are races on a.out. Could fix that, but
# it would also make output pretty confusing

libgetenv_multiple.a: libgetenv_multiple.a($(OBJS))
$(OBJS): getenv_multiple.h
getenv_preferences.o: alloca.h
alloca.h: alloca.in.h
	echo '#include <alloca.h>' | $(CC) $(CPPFLAGS) $(CFLAGS) -E - >/dev/null 2>&1 ; \
	sed "s/@HAVE_ALLOCA_H@/$$(( $$? == 0 ))/g" $<>$@
