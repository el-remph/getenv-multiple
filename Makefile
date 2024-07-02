# Build archives atomically (from the perspective of make -j, that is)
(%):%;
%.a: ; $(AR) rsv $@ $?

.PHONY = all clean
OBJS = getenv_multiple.o getenv_multiple_sorted.o getenv_preferences.o getenv_preferencev.o

all: libgetenv_multiple.a
libgetenv_multiple.a: libgetenv_multiple.a($(OBJS))
$(OBJS): getenv_multiple.h
clean:
	rm -fv libgetenv_multiple.a $(OBJS)
