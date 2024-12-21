#ifndef LISSA
#define LISSA
#include <stdio.h>

void replace_text(FILE *file, const char *pattern, const char *replacement);
void delete_lines(FILE *file, const char *pattern);
void insert_text(FILE *file, const char *text, int front);


#endif
