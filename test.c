/* Copyright (c) 2024 Sijmen J. Mulder. See LICENSE.txt */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "cmdsh.h"

static void
test_to_argv(void)
{
	static char buf[512];
	static char *argv[16];
	int argc;

	puts("to_argv: empty string");
	argc = to_argv("", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 0);
	assert(!argv[0]);

	puts("to_argv: single word");
	argc = to_argv("ls", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 1);
	assert(!strcmp(argv[0], "ls"));
	assert(!argv[1]);

	puts("to_argv: two words");
	argc = to_argv("ls code", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code"));
	assert(!argv[2]);

	puts("to_argv: whitespace");
	argc = to_argv("\tls  code ", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code"));
	assert(!argv[2]);

	puts("to_argv: backslash translation");
	argc = to_argv("ls code\\foo", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	puts("to_argv: slash to hyphen translation");
	argc = to_argv("ls /l", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!argv[2]);

	puts("to_argv: slash to hyphen translation, multiple");
	argc = to_argv("ls /l /a", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "-a"));
	assert(!argv[3]);

	puts("to_argv: multiple slash-arguments without space");
	argc = to_argv("ls/l/a", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "-a"));
	assert(!argv[3]);

	puts("to_argv: longopt slash to double hyphen translation");
	argc = to_argv("ls /l /all", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "--all"));
	assert(!argv[3]);

	puts("to_argv: longopt slash arguments without space");
	argc = to_argv("ls/l/all", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "--all"));
	assert(!argv[3]);

	puts("to_argv: empty quotes");
	argc = to_argv("ls \"\"", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], ""));
	assert(!argv[2]);

	puts("to_argv: quoted path");
	argc = to_argv("ls \"code/foo\"", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	puts("to_argv: embeded quoted part");
	argc = to_argv("ls code\"/\"foo", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	puts("to_argv: quoted spaces");
	argc = to_argv("ls \"code  foo\"", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code  foo"));
	assert(!argv[2]);

	puts("to_argv: quoted flags");
	argc = to_argv("ls -la", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-la"));
	assert(!argv[2]);

	puts("to_argv: no space between command and .");
	argc = to_argv("ls..", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], ".."));
	assert(!argv[2]);

	puts("to_argv: no space between command and ..");
	argc = to_argv("ls.", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "."));
	assert(!argv[2]);

	puts("to_argv: no space between command and ./path");
	argc = to_argv("ls.\\code", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "./code"));
	assert(!argv[2]);

	puts("to_argv: command with extension");
	argc = to_argv("ls.exe", buf, LEN(buf), argv, LEN(argv));
	assert(argc == 1);
	assert(!strcmp(argv[0], "ls.exe"));
	assert(!argv[1]);
}

int
main()
{
	test_to_argv();

	return 0;
}

