#include <stdio.h>
#include <stdbool.h>

#include "screen.h"
#include "output.h"
#include "input.h"
#include "wait.h"

int main()
{
    bool read = true;
    bool program = true;
    int key = 0;

    setEncoding(UTF8);

    do
    {
        drawMainScreen();

        while (read)
        {
            key = getChar(false);

            switch (key)
            {
            case 27:
                read = false;
                program = false;
                break;
            default:
                break;
            }
        }

    } while (program);

    return 0;
}