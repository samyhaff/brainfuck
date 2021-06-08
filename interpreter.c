#include <stdio.h>
#include <stdlib.h>

char *code;
char tape[30000] = {0};
char *ptr = tape;
int size;

void interpreter()
{
    int pc = 0;

    while (code[pc])
    {
        switch (code[pc])
        {
            case '>': ptr++; break;
            case '<': ptr--; break;
            case '+': ++*ptr; break;
            case '-': --*ptr; break;
            case '.': putchar(*ptr); break;
            case ',': *ptr = getchar(); break;
            case '[':
            {
                if (!*ptr)
                {
                    int loops_count = 1;
                    while (loops_count)
                    {
                        pc++;
                        if (pc >= size)
                        {
                            fprintf(stderr, "Error: unmatched square brackets\n");
                            exit(1);
                        }
                        if (code[pc] == '[')
                            loops_count++;
                        else if (code[pc] == ']')
                            loops_count--;
                    }
                }
                break;
            }
            case ']':
            {
                if (*ptr)
                {
                    int loops_count = 1;
                    while (loops_count)
                    {
                        pc--;
                        if (pc < 0)
                        {
                            fprintf(stderr, "Error: unmatched square brackets\n");
                            exit(1);
                        }
                        if (code[pc] == '[')
                            loops_count--;
                        else if (code[pc] == ']')
                            loops_count++;
                    }
                }
                break;
            }
        }
        pc++;
    }
}

int main(int argc, char **argv)
{
    FILE *file = fopen(argv[1], "r");
    int i = 0;
    char ch;

    if (argc < 2)
    {
        fprintf(stderr, "missing file path\n");
    exit(1);
    }

    if (file == NULL)
    {
        fprintf(stderr, "Couldn't open file\n");
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

    interpreter();

    return 0;
}
