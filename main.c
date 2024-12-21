#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "file.h"
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "./sed_simplified input.txt -r \"pattern\" \"replacement\"\n");
        fprintf(stderr, "./sed_simplified input.txt -d \"pattern\"\n");
        fprintf(stderr, "./sed_simplified input.txt -i -f \"text\"\n");
        fprintf(stderr, "./sed_simplified input.txt -i -b \"text\"\n");
        return 1;
    }

    const char *filename = argv[1];
    const char *command = argv[2];

    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }    
    
    if (strcmp(command, "-r") == 0)
    {
        if (argc != 5)
        {
            fprintf(stderr, "Invalid arguments for replace command\n");
            fclose(file);
            return 1;
        }
        replace_text(file, argv[3], argv[4]);
    }
    else if (strcmp(command, "-d") == 0)
    {
        if (argc != 4)
        {
            fprintf(stderr, "Invalid arguments for delete command\n");
            fclose(file);
            return 1;
        }
        delete_lines(file, argv[3]);
    }
    else if (strcmp(command, "-i") == 0)
    {
        if (argc != 5 || (strcmp(argv[3], "-f") != 0 && strcmp(argv[3], "-b") != 0))
        {
            fprintf(stderr, "Invalid arguments for insert command\n");
            fclose(file);
            return 1;
        }
	int front = strcmp(argv[3], "-f") == 0 ? 1 : 0;
        insert_text(file, argv[4], front);
    }
    
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        fclose(file);
        return 1;
    }
    
    fclose(file);
    return 0;
}
