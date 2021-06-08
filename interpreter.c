#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file = fopen(argv[1], "r");
    int i = 0;
    int size;
    char ch;
    char *code;

    if (argc < 2)
    {
        fprintf(stderr, "missing file path");
        exit(1);
    }

    if (file == NULL)
    {
        printf("Couldn't open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    code = malloc(size);

    while ((ch = fgetc(file)) != EOF)
        code[i++] = ch;
    code[i] = '\0';

    fclose(file);

    printf("%s", code);

    return 0;
}
