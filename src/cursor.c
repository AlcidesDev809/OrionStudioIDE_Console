#include <stdio.h>

#include "cursor.h"

void setCursor(_Bool states, int x, int y)
{
    if (states)
        printf("\x1b[?25h");
    else
        printf("\x1b[?25l");
    if (x > 0 && y > 0)
        printf("\x1b[%d;%dH", y, x);
}