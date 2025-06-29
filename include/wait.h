#ifndef WAIT_H
#define WAIT_H

#include "color.h"

typedef long long Time;

void wait(Time time);
void pause(const char *pauseText, Color color);
#endif // WAIT_H