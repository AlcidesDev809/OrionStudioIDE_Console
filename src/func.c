#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "func.h"
#include "screen.h"
#include "size.h"
#include "cursor.h"
#include "color.h"
#include "wait.h"
#include "output.h"
#include "input.h"

void drawMainScreen()
{
    const char *const options[] = {
        "[Esq] - Exit the program",
        "[^W] - Open Website",
        "[^G] - Open GitHub",
        "[^D] - Open Orion IDE"};

    const char *lines[] = {
        "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗",
        "║                                                                                                                      ║",
        "║    ██████╗ ██████╗ ██╗ ██████╗ ███╗   ██╗    ███████╗████████╗██╗   ██╗██████╗ ██╗ ██████╗     ██╗██████╗ ███████╗   ║",
        "║   ██╔═══██╗██╔══██╗██║██╔═══██╗████╗  ██║    ██╔════╝╚══██╔══╝██║   ██║██╔══██╗██║██╔═══██╗    ██║██╔══██╗██╔════╝   ║",
        "║   ██║   ██║██████╔╝██║██║   ██║██╔██╗ ██║    ███████╗   ██║   ██║   ██║██║  ██║██║██║   ██║    ██║██║  ██║█████╗     ║",
        "║   ██║   ██║██╔══██╗██║██║   ██║██║╚██╗██║    ╚════██║   ██║   ██║   ██║██║  ██║██║██║   ██║    ██║██║  ██║██╔══╝     ║",
        "║   ╚██████╔╝██║  ██║██║╚██████╔╝██║ ╚████║    ███████║   ██║   ╚██████╔╝██████╔╝██║╚██████╔╝    ██║██████╔╝███████╗   ║",
        "║    ╚═════╝ ╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝    ╚══════╝   ╚═╝    ╚═════╝ ╚═════╝ ╚═╝ ╚═════╝     ╚═╝╚═════╝ ╚══════╝   ║",
        "║                                                                                                                      ║",
        "╠═════════════════════════════════════════════════════════════════════════════════════════╤════════════════════════════╣",
        "║                                                                                         │                            ║",
        "║         Welcome to Orion Studio IDE (console), This software is a study version         │                            ║",
        "║         of the IDE Orion Studio IDE developed by me, you can see this and more          │                            ║",
        "║         of my projects Open Source in my account GitHub and in mine WebSite.            │                            ║",
        "║                                                                                         │                            ║",
        "║         If you have any suggestions for my projects, bug reports or                     │                            ║",
        "║         any recommendations for changing libraries, you can contact me                  │                            ║",
        "║         through forms present on my Website.                                            │                            ║",
        "║                                                                                         │                            ║",
        "║         Have fun 😎 !!!                                                                 │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "╟─────────────────────────────────────────────────────────────────────────────────────────┼────────────────────────────╢",
        "║         Waiting for character code input ...                                            │    MIT License (c) 2025    ║",
        "╚═════════════════════════════════════════════════════════════════════════════════════════╧════════════════════════════╝"};

    for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i)
        printc(";%s", 0xFFFFFF, lines[i]);

    for (size_t i = 0; i < sizeof(options) / sizeof(options[0]); i++)
    {
        setCursor(false, 94, 12 + i * 2);
        printc(";%s", 0xDDECFC, options[i]);
    }
}

void openEditorScreen()
{
    const char *const options[] = {
        "[ESQ] - Exit the program",
        "[^O] - Open File",
        "[^N] - New File",
        "[^S] - Save File"};

    bool program = true;
    bool read = true;
    int key = 0;
    char *buffer = NULL;
    size_t maxLenght = GiB(1);

    const char *lines[] = {
        "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗",
        "║   File name: Unnamed                                                                                                 ║",
        "╠═════════════════════════════════════════════════════════════════════════════════════════╤════════════════════════════╣",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "║                                                                                         │                            ║",
        "╟─────────────────────────────────────────────────────────────────────────────────────────┼────────────────────────────╢",
        "║                                                                                         │    MIT License (c) 2025    ║",
        "╚═════════════════════════════════════════════════════════════════════════════════════════╧════════════════════════════╝"};

    for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i)
        printc(";%s", 0xFFFFFF, lines[i]);

    for (size_t i = 0; i < sizeof(options) / sizeof(options[0]); i++)
    {
        setCursor(false, 94, 5 + i * 2);
        printc(";%s", 0xDDECFC, options[i]);
    }

    buffer = malloc(maxLenght);
    if (!buffer)
    {
        screenError("Memory error, closing the program ...");
        printf("Erro: alocação falhou.\n");
    }

    while (program)
    {
        while (read)
        {
            key = getChar(false);
            if (key == 27)
            {
                read = false;
                program = false;
            }
        }
    }

    free(buffer);
}