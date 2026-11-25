#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

static void include_file(const char *filename, FILE *out, int depth) {
    if (depth > 10) {
        printf("Error: include depth too deep in %s\n", filename);
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp) != NULL) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }

        if (strncmp(&line[i], "#include", 8) == 0) {
            int j = i + 8;
            while (line[j] == ' ' || line[j] == '\t') {
                j++;
            }

            if (line[j] == '"') {
                j++;
                char inc_name[256];
                int k = 0;

                while (line[j] != '\0' && line[j] != '"' && line[j] != '\n' && k < 255) {
                    inc_name[k] = line[j];
                    j++;
                    k++;
                }
                inc_name[k] = '\0';

                if (line[j] == '"') {
                    include_file(inc_name, out, depth + 1);
                    continue;
                }
            }
        }

        fputs(line, out);
    }

    fclose(fp);
}

void process_file_inclusion(const char *input, char *output) {
    FILE *out = fopen(output, "w");
    if (out == NULL) {
        printf("Error: cannot create %s\n", output);
        return;
    }

    include_file(input, out, 0);
    fclose(out);
}