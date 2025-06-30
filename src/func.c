#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <io.h>

#include "func.h"
#include "screen.h"
#include "size.h"
#include "cursor.h"
#include "color.h"
#include "wait.h"
#include "file.h"
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

void loadText(const char *buffer, size_t maxLength, int startX, int startY, int maxPerLine, int maxLines)
{
    int x = startX;
    int y = startY;

    for (size_t i = 0; i < maxLength && buffer[i] != '\0'; i++)
    {
        char c = buffer[i];

        if (c == '\n' || (x - startX) >= maxPerLine)
        {
            y++;
            x = startX;
            if (y >= startY + maxLines)
                break;

            if (c == '\n')
                continue;
        }

        setCursor(false, x, y);
        printc(";%c", 0xFFFFFF, c);
        x++;
    }
}

void clearText(int maxLines, int maxPerLine)
{
    for (int y = 4; y < 4 + maxLines; y++)
    {
        setCursor(false, 3, y);
        printc(";%*s", 0xFFFFFF, maxPerLine, "");
    }
}

void openEditorScreen()
{
    const char *const options[] = {
        "[ESQ] - Exit the program",
        "[^O] - Open File",
        "[^E] - Close File",
        "[^N] - New File",
        "[^D] - Delet File",
        "[^S] - Save File"};

    bool program = true;
    bool read = true;
    char *generalPointer = NULL;
    char *buffer = NULL;
    char *savedBuffer = NULL;
    const size_t maxLength = MiB(1);
    const int maxPerLine = 86;
    size_t cursorPosition = 0;
    const size_t maxChars = 1978;
    int cursorX = 0;
    int cursorY = 0;
    int currentLine = 0;
    const int maxLines = 23;
    int charCount = 0;

    (void)read;
    read = true;

    File *file = malloc(sizeof(File));
    if (!file)
    {
        screenError("Memory error: failed to allocate File struct");
        return;
    }

    file->isOpen = false;
    file->file = NULL;
    file->nameFile[0] = '\0';
    file->pathFile[0] = '\0';

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

    buffer = malloc(maxLength);
    savedBuffer = malloc(maxLength);
    if (!buffer || !savedBuffer)
    {
        free(buffer);
        free(savedBuffer);
        free(file);
        screenError("Memory error, closing the program ...");
        return;
    }
    memset(buffer, 0, maxLength);
    memset(savedBuffer, 0, maxLength);

    while (program)
    {
        cursorX = (charCount % maxPerLine) + 3;
        cursorY = (charCount / maxPerLine) + 4;

        if (cursorY > 26)
            cursorY = 26;

        setCursor(true, cursorX, cursorY);

        int firstByte = (unsigned char)getChar(false);
        int utf8_len = 1;
        unsigned char utf8_char[4];
        utf8_char[0] = firstByte;

        if (firstByte == EOF)
        {
            program = false;
            read = false;
            break;
        }

        if (firstByte < 128)
        {
            utf8_len = 1;
        }
        else if (firstByte >= 192 && firstByte <= 223)
        {
            utf8_len = 2;
            utf8_char[1] = (unsigned char)getChar(false);
        }
        else if (firstByte >= 224 && firstByte <= 239)
        {
            utf8_len = 3;
            utf8_char[1] = (unsigned char)getChar(false);
            utf8_char[2] = (unsigned char)getChar(false);
        }
        else if (firstByte >= 240 && firstByte <= 247)
        {
            utf8_len = 4;
            utf8_char[1] = (unsigned char)getChar(false);
            utf8_char[2] = (unsigned char)getChar(false);
            utf8_char[3] = (unsigned char)getChar(false);
        }
        else
        {
            continue;
        }

        if (firstByte == 27)
        {
            program = false;
            read = false;
        }
        else if (firstByte == 4)
        {
            if (file->isOpen)
            {
                char filepath[1024];
                strcpy(filepath, file->pathFile);

                closeFile(file);
                file->isOpen = false;
                memset(buffer, 0, maxLength);
                memset(savedBuffer, 0, maxLength);
                cursorPosition = 0;
                currentLine = 0;

                setCursor(false, 16, 2);
                printc(";%*s", 0xFFFFFF, 80, "");
                setCursor(false, 16, 2);
                printc(";%s", 0xFFFFFF, "Unnamed");

                clearText(maxLines, maxPerLine);

                loadText(buffer, maxLength, 3, 4, maxPerLine, maxLines);
                cursorPosition = strlen(buffer);

                if (remove(filepath) == 0)
                {
                    screenError("Error deleting file.");
                }
            }
            else
            {
                generalPointer = malloc(1024);
                getFilePath(generalPointer);

                if (remove(generalPointer) == 0)
                {
                    setCursor(false, 5, 28);
                    for (int i = 0; i < maxPerLine; i++)
                    {
                        printc(";%s", 0xFFFFFF, " ");
                    }
                    setCursor(false, 5, 28);
                    printc(";%s", 0xFFFFFF, "File deleted successfully!");
                }
                else
                {
                    screenError("Error deleting file.");
                }
                free(generalPointer);
            }
        }
        else if (firstByte == 5)
        {
            if (file->isOpen)
            {
                closeFile(file);
                file->isOpen = false;
                memset(buffer, 0, maxLength);
                memset(savedBuffer, 0, maxLength);
                cursorPosition = 0;
                currentLine = 0;

                setCursor(false, 16, 2);
                printc(";%*s", 0xFFFFFF, 80, "");
                setCursor(false, 16, 2);
                printc(";%s", 0xFFFFFF, "Unnamed");

                clearText(maxLines, maxPerLine);

                loadText(buffer, maxLength, 3, 4, maxPerLine, maxLines);
                cursorPosition = strlen(buffer);

                setCursor(false, 5, 28);
                for (int i = 0; i < maxPerLine; i++)
                {
                    printc(";%s", 0xFFFFFF, " ");
                }
                setCursor(false, 5, 28);
                printc(";%s", 0xFFFFFF, "File closed successfully!");

                cursorPosition = 0;
                charCount = 0;
                currentLine = 0;
            }
            else
            {
                screenError("No file is open to close.");
            }
        }
        else if (firstByte == 15)
        {
            if (!file->isOpen)
            {
                if (openFile(file, "a+"))
                {
                    file->isOpen = true;
                    memset(buffer, 0, maxLength);
                    memset(savedBuffer, 0, maxLength);
                    cursorPosition = 0;
                    currentLine = 0;

                    setCursor(false, 16, 2);
                    printc(";%*s", 0xFFFFFF, 80, "");
                    setCursor(false, 16, 2);
                    printc(";%s", 0xFFFFFF, file->nameFile);

                    for (unsigned int i = 0; i < maxLength; i++)
                    {
                        int c = fgetc(file->file);
                        if (c == EOF)
                            break;
                        buffer[i] = (char)c;
                        if (buffer[i] == '\n')
                        {
                            currentLine++;
                            if (currentLine >= 23)
                                break;
                        }
                    }

                    loadText(buffer, maxLength, 3, 4, maxPerLine, maxLines);
                    cursorPosition = strlen(buffer);
                    charCount = cursorPosition;

                    setCursor(false, 5, 28);
                    for (int i = 0; i < maxPerLine; i++)
                    {
                        printc(";%s", 0xFFFFFF, " ");
                    }
                    setCursor(false, 5, 28);
                    printc(";%s", 0xFFFFFF, "File open successfully!");
                }
                else
                {
                    printc(";Error opening file", 0xFF0000);
                }
            }
            else
            {
                screenError("File is already open, please close it before opening another one.");
            }
        }
        else if (firstByte == 19)
        {
            buffer[cursorPosition] = '\0';

            if (!file->isOpen)
            {
                if (openFile(file, "w"))
                {
                    fwrite(buffer, 1, cursorPosition, file->file);
                    fflush(file->file);
                    closeFile(file);
                    file->isOpen = false;

                    strncpy(savedBuffer, buffer, maxLength - 1);
                    savedBuffer[maxLength - 1] = '\0';

                    setCursor(false, 5, 28);
                    for (int i = 0; i < maxPerLine; i++)
                        printc(";%s", 0xFFFFFF, " ");
                    setCursor(false, 5, 28);
                    printc(";%s", 0xFFFFFF, "File saved successfully!");
                }
                else
                {
                    screenError("Error creating file to save.");
                }
            }
            else
            {
                rewind(file->file);
                fwrite(buffer, 1, cursorPosition, file->file);
                fflush(file->file);

                _chsize(_fileno(file->file), cursorPosition);

                strncpy(savedBuffer, buffer, maxLength - 1);
                savedBuffer[maxLength - 1] = '\0';

                setCursor(false, 5, 28);
                for (int i = 0; i < maxPerLine; i++)
                    printc(";%s", 0xFFFFFF, " ");
                setCursor(false, 5, 28);
                printc(";%s", 0xFFFFFF, "File saved successfully!");
            }
        }
        else if (firstByte == '\b' || firstByte == 127)
        {
            if (cursorPosition > 0)
            {
                printc(";\b \b", 0xFFFFFF);
                buffer[cursorPosition--] = '\0';
                if (charCount > 0)
                    charCount--;
            }
        }
        else if (firstByte >= 32 && firstByte < 255)
        {
            if (cursorPosition + utf8_len <= maxChars)
            {
                memcpy(&buffer[cursorPosition], utf8_char, utf8_len);
                cursorPosition += utf8_len;
                charCount++;
                printc(";%.*s", 0xFFFFFF, utf8_len, (char *)utf8_char);
            }
            else
            {
                setCursor(false, 5, 28);
                printc(";%s", 0xFF0000, "Limite máximo de caracteres atingido!");
            }
        }
    }
    free(buffer);
    free(savedBuffer);
    closeFile(file);
    free(file);
}