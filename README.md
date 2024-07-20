cmd-sh
======
CMD - (S)hell from (H)ell

Unix shell with CMD.EXE / COMMAND.COM syntax.

Example:

    C:> ls/p/all code\foo

Is equivalent to:

    $ ls -p --all code/foo

The evil CMD syntax is transformed into a Unix process invocation with
the following rules:

 1. Every `/` starts a new argument (e.g. a space is inserted).
 2. Every `/` is transformed into a `-` if one character follows it, or
    `--` if more than one character follows it.
 3. Every '\' is transformed into `/`
 4. Anything `"in quotes"`  is ignored.

Building
--------
Should work on any Unix-like (Linux, BSD, macOS) without further
dependencies.

    make 
    make check

Author
------
Sijmen J. Mulder
