/*
 * This file should stay unchanged.
 * Read README for more info.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <getopt.h>

#include "sort_impl.h"

#define STREQ(a, b) (strcmp(a, b) == 0)
#define ERROR(...) \
do { \
    fprintf(stderr, "ERROR %s:%d : ", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while (0)

#define SYS_ERROR(...) \
do { \
    char ebuf[1024]; \
    strerror_r(errno, ebuf, sizeof(ebuf)); \
    fprintf(stderr, "System error %s:%d : ", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, " : %s\n", ebuf); \
    fprintf(stderr, "\n"); \
} while (0)


static void
print_help(const char *progname)
{
    fprintf(stderr,
            "Usage: %s [--help][--reverse] [FILE]\n"
            "\n"
            "Sort lines read from FILE and write them to standard output.\n"
            "If FILE is not specified, or is -, read standard input.\n"
            "\n"
            "Options:\n"
            "\t-h | --help\t\tdisplay this help and exit\n"
            "\t-r | --reverse\t\treverse the result of comparisons\n",
            progname);
}


static FILE *
openFile(const char *filename)
{
    FILE *fp = NULL;
    const char *pathname = filename;

    if (STREQ(filename, "-"))
        pathname = "/dev/stdin";

    if (!(fp = fopen(pathname, "r")))
        SYS_ERROR("Unable to open %s", pathname);

    return fp;
}


int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;
    Sort *s = NULL;
    FILE *fp = NULL;
    const char *filename = "-";
    char *line = NULL;
    size_t lineLen = 0;
    ssize_t nread = 0;
    bool reverse = false;
    int arg, longindex = -1;
    struct option opt[] = {
        {"help", no_argument, NULL, 'h'},
        {"reverse", no_argument, NULL, 'r'},
        {NULL, 0, NULL, 0},
    };

    if (!setlocale(LC_ALL, "")) {
        SYS_ERROR("Unable to set locale");
        goto cleanup;
    }

    while ((arg = getopt_long(argc, argv, "+:hr", opt, &longindex)) != -1) {
        switch (arg) {
        case 'h':
            print_help(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        case 'r':
            reverse = true;
            break;

        case '?':
            if (optopt)
                ERROR("unsupported option '-%c'. See --help.", optopt);
            else
                ERROR("unsupported option '%s'. See --help.", argv[optind - 1]);
            exit(EXIT_FAILURE);
        default:
            ERROR("unknown option");
            exit(EXIT_FAILURE);
        }
        longindex = -1;
    }

    if (argc > optind)
        filename = argv[optind];

    if (!(s = sort_init())) {
        SYS_ERROR("Unable to create sort object");
        goto cleanup;
    }

    if (!(fp = openFile(filename)))
        goto cleanup;

    while ((nread = getline(&line, &lineLen, fp)) != -1) {
        if (sort_append_line(s, line, lineLen) < 0) {
            ERROR("Unable to add line");
            goto cleanup;
        }
    }

    sort_sort(s, reverse);

    sort_print(s, stdout);

    ret = EXIT_SUCCESS;

 cleanup:
    free(line);
    if (fp)
        fclose(fp);
    sort_free(s);
    return ret;
}
