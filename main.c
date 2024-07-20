/* Copyright (c) 2024 Sijmen J. Mulder. See LICENSE.txt */

#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include "cmdsh.h"

int
main()
{
	char input[512], buf[512], *argv[64];
	int argc;

	/* a banner for extra Redmond vibes */
	printf("cmd-sh, the shell from hell\n");
	printf("Copyright (c) 2024 Sijmen J. Mulder\n");

	while (!feof(stdin)) {
		cmd_prompt(input, sizeof(input));
		argc = to_argv(input, buf, sizeof(buf), argv,
		    LEN(argv));
		if (argc == -1)
			warnx("parsing error");
		else if (argc > 0)
			cmd_eval(argv);
	}

	return 0;
}
