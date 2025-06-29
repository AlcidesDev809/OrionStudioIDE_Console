#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "wait.h"
#include "color.h"
#include "output.h"

void wait(Time time)
{
    Sleep((DWORD)time);
}

void pause(const char *pauseText, Color color)
{
    int length = strlen(pauseText);
    char *buffer = NULL;

    length += 2;

    buffer = malloc(length);
    if (buffer == NULL)
        return;
    snprintf(buffer, length, ";%s", pauseText);
    printc(buffer, color);
    free(buffer);

    system("pause > nul");
}
