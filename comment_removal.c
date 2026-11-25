#include <stdio.h>
#include "preprocessor.h"

void remove_comments(const char *src, const char *out) {
    FILE *in = fopen(src, "r");
    FILE *fp = fopen(out, "w");

    if (in == NULL || fp == NULL) {
        if (in != NULL) fclose(in);
        if (fp != NULL) fclose(fp);
        return;
    }

    int ch;
    int in_line = 0;
    int in_block = 0;

    while ((ch = fgetc(in)) != EOF) {
        if (in_line) {
            if (ch == '\n') {
                in_line = 0;
                fputc('\n', fp);
            }
            continue;
        }

        if (in_block) {
            if (ch == '*') {
                int next = fgetc(in);
                if (next == '/') {
                    in_block = 0;
                } else if (next == EOF) {
                    break;
                }
            }
            continue;
        }

        if (ch == '/') {
            int next = fgetc(in);
            if (next == '/') {
                in_line = 1;
            } else if (next == '*') {
                in_block = 1;
            } else {
                fputc('/', fp);
                if (next != EOF) {
                    fputc(next, fp);
                }
            }
        } else {
            fputc(ch, fp);
        }
    }

    fclose(in);
    fclose(fp);
}