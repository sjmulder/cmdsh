/* Copyright (c) 2024 Sijmen J. Mulder. See LICENSE.txt */

#define LEN(a)	((sizeof(a))/sizeof(*(a)))

int to_argv(const char *input,
    char *buf, size_t buf_sz,
    char **argv, size_t argv_len);
