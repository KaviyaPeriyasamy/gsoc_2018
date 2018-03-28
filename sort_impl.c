/*
 * sort_impl.c: Implementation of sort functions
 *
 * Before modifying this file read README.
 */

#include <stdlib.h>
#include <string.h>

#include "sort_impl.h"

/**
 * sort_init:
 *
 * Allocate and init Sort object.
 *
 * Returns: pointer to allocated object on success,
 *          NULL otherwise.
 */
Sort *
sort_init(void)
{
    /* Implement me. */
}


/**
 * sort_free:
 * @s: sort object
 *
 * Frees any previously allocated object.
 */
void
sort_free(Sort *s)
{
    /* Implement me. */
}


/**
 * sort_append_line:
 * @s: sort object
 * @line: pointer to buffer
 * @lineLen: size of @line
 *
 * Appends line to @s sort object. @line contains @lineLen
 * characters.
 *
 * Returns: 0 on success,
 *         -1 otherwise.
 */
int
sort_append_line(Sort *s,
                 const char *line,
                 size_t lineLen)
{
    /* Implement me. */
}


/**
 * sort_print:
 * @s: sort object
 * @fp: output stream
 *
 * Prints previously appended lines to sort object @s into output
 * stream @fp.
 */
void
sort_print(Sort *s,
           FILE *fp)
{

    /* Implement me. */
}


/**
 * sort_sort:
 * @s: sort object
 * @cb: sort callback
 * @reverse: if true, do reverse sorting
 *
 * Sorts lines contained in @s using @cb for comparison
 * alphabetically (ascending, a-z). However, if @reverse is true,
 * the order is reversed and thus descending, z-a).
 */
void
sort_sort(Sort *s,
          sortCB cb,
          bool reverse)
{
    /* Implement me. */
}
