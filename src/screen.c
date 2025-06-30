#include <stdio.h>
#include <windows.h>

#include "screen.h"

void screenError(const char *const message)
{
    MessageBox(NULL, message, "Error", MB_OK | MB_ICONERROR);
}
