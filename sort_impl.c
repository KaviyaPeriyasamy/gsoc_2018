/*
 * sort_impl.c: Implementation of sort functions
 *
 * Before modifying this file read README.
 */

#include <stdlib.h>
#include <string.h>

#include "sort_impl.h"

typedef struct _Line Line;
struct _Line {
    char *line;
    Line *next;
};

struct _Sort {
    Line *l;
};


static void
line_free(Line *l)
{
    if (!l)
        return;

    free(l->line);
    free(l);
}


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
    Sort *s;

    if (!(s = malloc(sizeof(*s))))
        return NULL;

    s->l = NULL;

    return s;
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
    Line *l;

    if (!s)
        return;

    l = s->l;
    while (l) {
        Line *next = l->next;

        line_free(l);
        l = next;
    }

    free(s);
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
    Line *l = NULL;
    int ret = -1;

    if (!s)
        return -1;

    if (!(l = malloc(sizeof(*l))))
        return -1;
    l->next = NULL;

    if (!(l->line = malloc(lineLen * sizeof(char) + 1)))
        goto cleanup;

    memcpy(l->line, line, lineLen * sizeof(char));
    l->line[lineLen] = '\0';

    if (s->l) {
        Line *tmp = s->l;
        while (tmp && tmp->next)
            tmp = tmp->next;
        tmp->next = l;
    } else {
        s->l = l;
    }

    l = NULL;

    ret = 0;
 cleanup:
    line_free(l);
    return ret;
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
    Line *l;

    if (!s)
        return;

    l = s->l;
    while (l) {
        fputs(l->line, fp);
        l = l->next;
    }
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
    if (!s || !s->l || !s->l->next)
        return;

    while (1) {
        Line *l = s->l;
        bool xchg = false;

        while (l && l->next) {
            int cmp = cb(l->line, l->next->line);

            if ((!reverse && cmp > 0) ||
                (reverse && cmp < 0)) {
                char *tmp = l->line;
                l->line = l->next->line;
                l->next->line = tmp;
                xchg = true;
            }

            l = l->next;
        }

        if (!xchg)
            break;
    }
}
