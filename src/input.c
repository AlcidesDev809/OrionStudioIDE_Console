#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#include "input.h"

char getChar(_Bool showCharacter)
{
    int c = showCharacter ? getchar() : getch();
    return (char)(c == EOF ? EOF : c);
}
