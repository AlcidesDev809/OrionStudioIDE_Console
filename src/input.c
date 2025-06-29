#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#include "input.h"

int getChar(_Bool showCharacter)
{
    if (showCharacter)
        return getchar();
    else
        return getch();
}
