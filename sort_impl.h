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

void
sort_sort(Sort *s, bool reverse);
