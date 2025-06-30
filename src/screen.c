#include <stdio.h>
#include <windows.h>
#include <process.h>

#include "screen.h"

void screenError(const char *const message)
{
    SetProcessDPIAware();
    
    MessageBox(NULL, message, "Error", MB_OK | MB_ICONERROR);
}
