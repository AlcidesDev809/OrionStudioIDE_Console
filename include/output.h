#ifndef OUTPUT_H
#define OUTPUT_H

typedef enum
{
    UTF8
} EncodingCode;

int printc(const char *format, ...);

void setEncoding(EncodingCode encodingCode);

#endif // OUTPUT_H