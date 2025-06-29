#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "wait.h"

void wait(Time time)
{
#ifdef _WIN32
    Sleep((DWORD)time);
#else
    struct timespec ts;
    ts.tv_sec = time / 1000;
    ts.tv_nsec = (time % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}
