# C Preprocessor Implementation

A custom C preprocessor written in C that simulates the core preprocessing stages of a C compiler before compilation.

## Features
- **Comment Removal (`comment_removal.c`):** Strips single-line (`//`) and multi-line (`/* ... */`) comments while preserving string literals and line formatting.
- **Header File Inclusion (`file_inclusion.c`):** Resolves local `#include "filename"` directives (such as `extra.h`) and inserts their contents into the source stream.
- **Macro Expansion (`macro_handler.c`):** Parses `#define` directives and replaces macro identifiers with their defined values across the code.

## Project Structure
- `main.c` — Entry point coordinating the preprocessing pipeline
- `preprocessor.h` — Shared function declarations and data structures
- `comment_removal.c` — Comment stripping logic
- `file_inclusion.c` — Header inclusion handler
- `macro_handler.c` — Macro definition and substitution logic
- `Makefile` — Build configuration for GCC
- `sample.c` & `extra.h` — Sample C source and header files for testing

## Build & Run

Compile using `make`:
```bash
make
