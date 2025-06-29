#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "strformat.h"

int isEmpty(const char *string)
{
    if (string == NULL)
        return true;

    while (*string)
    {
        if (!isspace((unsigned char)*string))
            return false;
        string++;
    }

    return true;
}