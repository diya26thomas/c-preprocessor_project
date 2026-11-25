#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define MAX_MACROS 64
#define MAX_PARAMS 8
#define MAX_LINE 1024

typedef struct {
    char name[64];
    int is_func;
    int param_count;
    char params[MAX_PARAMS][32];
    char body[256];
} Macro;

/* Module 1: Comment removal */
void remove_comments(const char *src, const char *out);

/* Module 2: File inclusion */
void process_file_inclusion(const char *input, char *output);

/* Module 3: Macro handling */
void process_macros(const char *input, char *output);

#endif