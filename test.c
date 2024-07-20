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
	const char *input;
	int argc;

	printf("to_argv: %s\n", input = "");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 0);
	assert(!argv[0]);

	printf("to_argv: %s\n", input = "ls");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 1);
	assert(!strcmp(argv[0], "ls"));
	assert(!argv[1]);

	printf("to_argv: %s\n", input = "ls code");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "\tls   code ");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls code\\foo");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls /l");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls /l /a");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "-a"));
	assert(!argv[3]);

	printf("to_argv: %s\n", input = "ls/l/a");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "-a"));
	assert(!argv[3]);

	printf("to_argv: %s\n", input = "ls /l /all");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "--all"));
	assert(!argv[3]);

	printf("to_argv: %s\n", input = "ls/l/all");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 3);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-l"));
	assert(!strcmp(argv[2], "--all"));
	assert(!argv[3]);

	printf("to_argv: %s\n", input = "ls \"code/foo\"");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls \"code/foo\"");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls \"code/\"foo");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code/foo"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls \"code  foo\"");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "code  foo"));
	assert(!argv[2]);

	printf("to_argv: %s\n", input = "ls -la");
	argc = to_argv(input, buf, LEN(buf), argv, LEN(argv));
	assert(argc == 2);
	assert(!strcmp(argv[0], "ls"));
	assert(!strcmp(argv[1], "-la"));
	assert(!argv[2]);
}

int
main()
{
	test_to_argv();

	return 0;
}

