#ifndef FILE_H
#define FILE_H

typedef struct
{
    FILE *file;
    char nameFile[1024];
    char pathFile[1024];
    _Bool isOpen;
} File;

void getFilePath(char *buffer);

void closeFile(File *fileStruct);

int openFile(File *fileStruct, const char *mode);

#endif // FILE_H