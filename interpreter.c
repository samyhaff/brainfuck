#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    char ch;

    if (argc < 2)
    {
        fprintf(stderr, "missing file path");
        exit(1);
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Couldn't open file");
        exit(1);
    }

    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(file);

    return 0;
}
