#include <stdio.h>
#include <stdbool.h>
#include "input.h"

#ifdef _WIN32
#include <conio.h>

int getChar(_Bool showCharacter)
{
    if (showCharacter)
        return getchar();
    else
        return getch();
}

#else

int getChar(_Bool showCharacter)
{
    if (showCharacter)
        return getchar();
    else
    {
    }
}
#endif
