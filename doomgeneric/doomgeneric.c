#include "doomgeneric.h"

uint32_t* DG_ScreenBuffer = 0;


void dg_Create()
{
	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);

	DG_Init();
}

/*void fprintf(FILE *file, char *str)
{
    printf("fprintf(%s) called\n", str);
}*/

void putchar(char c)
{
    printf("%c", c);
}

void puts(char *str)
{
    printf("%s\n", str);
}

int isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f')
        return 1;

    return 0;
}
