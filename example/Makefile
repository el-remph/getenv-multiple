# This is meant to be called by ../Makefile, with -j1 forced,
# libgetenv_multiple.a built, maybe called a few times with different
# standards
#
# Just runs some tests

all: test_confdir test_git_editor
	rm a.out

test_confdir:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -DTEST confdir.c ../libgetenv_multiple.a
	test "`./a.out`" = "$$HOME/.config/foo"
	test "`XDG_CONFIG_DIR=foobar ./a.out`" = foobar/foo
# much originality in the naming there

test_git_editor:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -DTEST git_editor.c ../libgetenv_multiple.a
	test "`GIT_EDITOR=nano VISUAL=vim EDITOR=ex ./a.out`" = nano
	test "`VISUAL=vim EDITOR=ex ./a.out`" = vim
