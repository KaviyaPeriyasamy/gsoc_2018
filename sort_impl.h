/*
 * sort_impl.h: Header file exporting sort functions
 *
 * Before modifying this file read README.
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct _Sort Sort;

Sort *
sort_init(void);

void
sort_free(Sort *s);

int
sort_append_line(Sort *s, const char *line, size_t lineLen);

void
sort_print(Sort *s, FILE *fp);

/**
 * sortCB:
 * @s1: input string
 * @s2: input string
 *
 * Function compares the two strings s1 and s2. It returns an integer less
 * than, equal to, or greater than zero if s1 is found, respectively, to be
 * less than, to match, or be greater than s2.
 */
typedef int (*sortCB)(const char *s1,
                      const char *s2);

void
sort_sort(Sort *s, sortCB cb, bool reverse);
