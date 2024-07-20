cmdsh
=====
CMD (S)hell from (H)ell

Unix shell with CMD.EXE/COMMAND.COM-like syntax.

Example:

    C:\home\sjmulder>ls/l/all code\foo
    C:\home\sjmulder>cd..\john

Is equivalent to:

    $ ls -l --all code/foo
    $ cd ../john

The evil CMD syntax is transformed into a Unix process invocation with
the following rules:

 1. Every `/` starts a new argument (i.e. a space is inserted).
 2. Every `/` is transformed into a `-` if one character follows it, or
    `--` if more than one character follows it.
 3. Every `\` is transformed into `/`.
 4. Anything `"in quotes"`  is ignored.
 5. `.`, `..` and paths starting with `.\` or `..\` are split from the
    command name.

Goals & non-goals
-----------------
Goals
 - Provide a Unix shell that, syntax-wise, *feels* like CMD.
 - Frustrate users to no end with surprising mappings of CMD-isms to the
   Unix world.
 - Actually make it somewhat useable.

Non-goals;
 - Compatibility with actual CMD commands (beyond some builtins) or
   batch scripts. It's a Unix shell, not a DOS emulator.

This shell is not for serious use (but people are still using
[ed(1)](https://man.openbsd.org/ed) so who knows). Many important
features are missing, such as interrupt handling, variables, pipes,
output redirection and control flow statements. See [TODO](TODO.md).

Building
--------
Should work on any Unix-like (Linux, BSD, macOS) without further
dependencies.

    make
    sudo make install
    echo '/usr/local/cmdsh' | sudo tee -a /etc/shells >/dev/null

Author
------
Copyright (c) 2024 Sijmen J. Mulder (<ik@sjmulder.nl>). Licensed under
the GNU GPL 3.0 or any later version. See [license](LICENSE.txt).
