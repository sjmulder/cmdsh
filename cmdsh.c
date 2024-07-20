/* Copyright (c) 2024 Sijmen J. Mulder. See LICENSE.txt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>
#include "cmdsh.h"

int
to_argv(const char *input,
    char *buf, size_t buf_sz,
    char **argv, size_t argv_len)
{
	const char *s;	/* into input */
	char *d;	/* into buf */
	int argc=0;
	int in_arg=0;
	int in_quotes=0;

	if (!input || !buf || !argv || !argv_len)
		return -1;
	
	for (s=input, d=buf; *s; s++) {
		if (d >= buf+buf_sz-4)		/* \0 + 3 chars + \0 */
			return -1;
		if ((size_t)argc >= argv_len-1)	/* final NULL */
			return -1;

		if (in_quotes) {
			if (*s == '\"') in_quotes = 0; else *d++ = *s;
		} else if (*s == '\"') {
			if (!in_arg) argv[argc++] = d;
			in_arg = 1;
			in_quotes = 1;
		} else if (isspace((int)*s)) {
			if (in_arg) *d++ = '\0';
			in_arg = 0;
		} else if (*s == '.' && in_arg && argc == 1 && (!s[1]
		    || s[1] == '/' || s[1] == '\\' || s[1] == '.'
		    || isspace((int)s[1]))) {
			*d++ = '\0';
			argv[argc++] = d;
			*d++ = *s;
		} else if (*s == '/') {
			if (in_arg) *d++ = '\0';
			argv[argc++] = d;
			in_arg = 1;
			if (s[1] && s[2] && s[2]!='/' && !isspace((int)s[2]))
				*d++ = '-';
			*d++ = '-';
		} else {
			if (!in_arg) argv[argc++] = d;
			in_arg = 1;
			if (*s == '\\') *d++ = '/'; else *d++ = *s;
		}
	}

	if (in_arg)
		*d++ = '\0';
	
	argv[argc] = NULL;
	return argc;
}

void
cmd_prompt(char *buf, size_t buf_sz)
{
	static char cwd[512];
	int i;

	if (getcwd(cwd, sizeof(cwd))) {
		for (i=0; cwd[i]; i++)
			if (cwd[i] == '/')
				cwd[i] = '\\';
		printf("\nC:%s>", cwd);
	} else
		printf("\n...>");

	fflush(stdout);
	fgets(buf, buf_sz, stdin);
}

void
cmd_eval(int argc, char **argv)
{
	pid_t pid;

	assert(argc > 0);
	assert(argv[0]);

	if (!strcasecmp(argv[0], "exit")) {
		if (argc != 1)
			warnx("too many arguments for EXIT");
		else
			exit(0);
	} else if (!strcasecmp(argv[0], "cd")) {
		if (argc != 2)
			warnx("too many arguments for CD");
		else if (chdir(argv[1]) == -1)
			warn(NULL);
	} else switch ((pid = fork())) {
	case -1:
		warn("%s", argv[0]);
		break;
	case 0:
		execvp(argv[0], argv);
		warn("%s", argv[0]);
		break;
	default:
		waitpid(pid, NULL, 0);
		break;
	}
}
