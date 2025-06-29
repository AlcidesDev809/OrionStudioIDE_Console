#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "strformat.h"
#include "color.h"
#include "output.h"

int printc(const char *format, ...)
{
    if (isEmpty(format))
        return -1;

    va_list args;
    va_start(args, format);

    va_list argsDup;
    int length = 0;
    char *buffer = NULL;
    int ret = -1;

    if (format[0] == ';')
    {
        Color color = va_arg(args, Color);
        format++;

        va_copy(argsDup, args);
        length = vsnprintf(NULL, 0, format, argsDup);
        va_end(argsDup);

        if (length < 0)
            goto cleanup;

        length++;
        buffer = malloc(length);
        if (!buffer)
            goto cleanup;

        ret = vsnprintf(buffer, length, format, args);
        if (ret < 0)
            goto cleanup;

        printf("\x1b[38;2;%d;%d;%dm", getRValue(color), getGValue(color), getBValue(color));
        printf("%s", buffer);
        printf("\x1b[0m");
    }
    else
    {
        va_copy(argsDup, args);
        length = vsnprintf(NULL, 0, format, argsDup);
        va_end(argsDup);

        if (length < 0)
            goto cleanup;

        length++;
        buffer = malloc(length);
        if (!buffer)
            goto cleanup;

        ret = vsnprintf(buffer, length, format, args);
        if (ret < 0)
            goto cleanup;

        printf("%s", buffer);
    }

cleanup:
    free(buffer);
    va_end(args);
    return ret;
}

void setEncoding(EncodingCode encodingCode)
{
    if (encodingCode == UTF8)
        system("chcp 65001 > nul");
}