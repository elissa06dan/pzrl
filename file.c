#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024

void replace_text(FILE *file, const char *pattern, const char *replacement) {
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED);
    char line[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];

    rewind(file);
    FILE *temp = tmpfile();

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *cursor = line;
        regmatch_t match;
        buffer[0] = '\0';

        while (regexec(&regex, cursor, 1, &match, 0) == 0) {
            strncat(buffer, cursor, match.rm_so);
            strcat(buffer, replacement);
            cursor += match.rm_eo;
        }
        strcat(buffer, cursor);
        fprintf(temp, "%s", buffer);
    }
    
    rewind(file);
    rewind(temp);
    freopen(NULL, "w", file);
    while (fgets(line, MAX_LINE_LENGTH, temp)) {
        fprintf(file, "%s", line);
    }

    fclose(temp);
    regfree(&regex);
}


void delete_lines(FILE *file, const char *pattern) {
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED);
    char line[MAX_LINE_LENGTH];

    rewind(file);
    FILE *temp = tmpfile();

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (regexec(&regex, line, 0, NULL, 0) != 0) {
            fprintf(temp, "%s", line);
        }
    }

    rewind(file);
    rewind(temp);
    freopen(NULL, "w", file);
    
    while (fgets(line, MAX_LINE_LENGTH, temp)) {
    fprintf(file, "%s", line);
    }

    fclose(temp);
    regfree(&regex);
}

void insert_text(FILE *file, const char *text, int front) {
    char line[MAX_LINE_LENGTH];

    rewind(file);
    FILE *temp = tmpfile();

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line[strcspn(line, "\n")] = '\0';
        if (front) {
            fprintf(temp, "%s%s\n", text, line);
        } else {
            fprintf(temp, "%s%s\n", line, text);
        }
    }

    rewind(file);
    rewind(temp);
    freopen(NULL, "w", file);
    while (fgets(line, MAX_LINE_LENGTH, temp)) {
        fprintf(file, "%s", line);
    }

    fclose(temp);
}
