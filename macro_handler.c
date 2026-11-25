#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

static int is_name_char(char c) {
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            (c == '_'));
}

static int is_name_start(char c) {
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_'));
}

void process_macros(const char *input, char *output) {
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if (in == NULL || out == NULL) {
        if (in != NULL) fclose(in);
        if (out != NULL) fclose(out);
        return;
    }

    Macro macros[MAX_MACROS];
    int count = 0;

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, in) != NULL) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }

        /* Handle #define NAME VALUE */
        if (strncmp(&line[i], "#define", 7) == 0 &&
            (line[i + 7] == ' ' || line[i + 7] == '\t')) {
            int j = i + 7;
            while (line[j] == ' ' || line[j] == '\t') {
                j++;
            }

            char name[64];
            int n = 0;
            while (is_name_char(line[j]) && n < 63) {
                name[n] = line[j];
                j++;
                n++;
            }
            name[n] = '\0';

            if (n > 0 && count < MAX_MACROS) {
                while (line[j] == ' ' || line[j] == '\t') {
                    j++;
                }

                char value[256];
                int v = 0;
                while (line[j] != '\0' && line[j] != '\n' && line[j] != '\r' && v < 255) {
                    value[v] = line[j];
                    j++;
                    v++;
                }
                value[v] = '\0';

                while (v > 0 && (value[v - 1] == ' ' || value[v - 1] == '\t')) {
                    v--;
                    value[v] = '\0';
                }

                strcpy(macros[count].name, name);
                strcpy(macros[count].body, value);
                macros[count].is_func = 0;
                macros[count].param_count = 0;
                count++;
            }
            continue;
        }

        /* Replace macro names in normal lines */
        char result[MAX_LINE * 2];
        int r = 0;
        int pos = 0;

        while (line[pos] != '\0' && r < (MAX_LINE * 2) - 2) {
            if (is_name_start(line[pos]) &&
                (pos == 0 || !is_name_char(line[pos - 1]))) {
                char word[64];
                int w = 0;
                int k = pos;

                while (is_name_char(line[k]) && w < 63) {
                    word[w] = line[k];
                    k++;
                    w++;
                }
                word[w] = '\0';

                int found = -1;
                for (int m = 0; m < count; m++) {
                    if (strcmp(word, macros[m].name) == 0) {
                        found = m;
                        break;
                    }
                }

                if (found != -1) {
                    int b = 0;
                    while (macros[found].body[b] != '\0' && r < (MAX_LINE * 2) - 2) {
                        result[r] = macros[found].body[b];
                        r++;
                        b++;
                    }
                    pos = k;
                    continue;
                }
            }

            result[r] = line[pos];
            r++;
            pos++;
        }
        result[r] = '\0';

        fputs(result, out);
    }

    fclose(in);
    fclose(out);
}
