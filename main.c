#include <stdio.h>
#include "preprocessor.h"

int main(void) {
    const char *input_file = "sample.c";
    const char *step1_file = "step1_nocomments.c";
    const char *step2_file = "step2_included.c";
    char *output_file = "output.c";

    remove_comments(input_file, step1_file);
    process_file_inclusion(step1_file, (char *)step2_file);
    process_macros((char *)step2_file, output_file);

    printf("Preprocessing completed. Output written to %s\n", output_file);
    return 0;
}