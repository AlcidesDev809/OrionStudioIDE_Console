#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "screen.h"
#include "output.h"
#include "input.h"
#include "wait.h"

int main()
{
    bool read = true;
    bool program = true;
    bool initProgram = false;
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
            case 4:
                read = false;
                program = false;
                initProgram = true;
                break;
            case 7:
                ShellExecuteW(NULL, L"open", L"https://github.com/AlcidesDev809", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 23:
                ShellExecuteW(NULL, L"open", L"https://alcides-dev.web.app/", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 27:
                read = false;
                program = false;
                break;
            default:
                break;
            }
        }

    } while (program);

    if (initProgram)
    {
        system("cls");
        openEditorScreen();
    }

    return 0;
}