cmd-sh
======
CMD - (S)hell from (H)ell

Unix shell with CMD.EXE/COMMAND.COM-like syntax.

Example:

    C:\home\sjmulder>ls/l/all code\foo
    C:\home\sjmulder>cd..\john

Is equivalent to:

    $ ls -l --all src/foo
    $ cd ../john

The evil CMD syntax is transformed into a Unix process invocation with
the following rules:

 1. Every `/` starts a new argument (e.g. a space is inserted).
 2. Every `/` is transformed into a `-` if one character follows it, or
    `--` if more than one character follows it.
 3. Every '\' is transformed into `/`.
 4. Anything `"in quotes"`  is ignored.
 5. `.`, `..` and paths starting with `.\` or `..\` are split from the
    command name.

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
the GNU GPL 3.0 or any later version. See LICENSE.txt.
