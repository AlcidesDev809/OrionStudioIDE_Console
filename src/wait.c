#include <windows.h>

#include "wait.h"

void wait(Time time)
{
    Sleep((DWORD)time);
}
