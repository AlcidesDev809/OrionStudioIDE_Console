#include <windows.h>
#include <shobjidl.h>
#include <stdio.h>
#include <string.h>

#include "file.h"

int openFile(File *fileStruct, const char *mode)
{
    if (fileStruct == NULL || mode == NULL)
        return 0;

    if (!fileStruct->isOpen)
    {
        getFilePath(fileStruct->pathFile);
        fileStruct->file = NULL;
        fopen_s(&fileStruct->file, fileStruct->pathFile, mode);
        if (fileStruct->file == NULL)
            return 0;

        char *lastSlash = strrchr(fileStruct->pathFile, '\\');
        if (lastSlash != NULL)
            strcpy(fileStruct->nameFile, lastSlash + 1);
        else
            strcpy(fileStruct->nameFile, fileStruct->pathFile);

        return 1;
    }
    return 0;
}


void closeFile(File *fileStruct)
{
    if (fileStruct->file != NULL)
        fclose(fileStruct->file);
    fileStruct->file = NULL;
    fileStruct->isOpen = 0;
    memset(fileStruct->nameFile, 0, sizeof(fileStruct->nameFile));
    memset(fileStruct->pathFile, 0, sizeof(fileStruct->pathFile));
}

void getFilePath(char *buffer)
{
    SetProcessDPIAware();

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen = NULL;
        hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                              &IID_IFileOpenDialog, (void **)&pFileOpen);

        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            if (SUCCEEDED(pFileOpen->lpVtbl->GetOptions(pFileOpen, &dwOptions)))
            {
                pFileOpen->lpVtbl->SetOptions(pFileOpen, dwOptions | FOS_FILEMUSTEXIST);
            }

            hr = pFileOpen->lpVtbl->Show(pFileOpen, NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->lpVtbl->GetResult(pFileOpen, &pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->lpVtbl->GetDisplayName(pItem, SIGDN_FILESYSPATH, &pszFilePath);
                    if (SUCCEEDED(hr))
                    {
                        size_t outSize;
                        wcstombs_s(&outSize, buffer, MAX_PATH, pszFilePath, _TRUNCATE);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->lpVtbl->Release(pItem);
                }
            }
            pFileOpen->lpVtbl->Release(pFileOpen);
        }
        CoUninitialize();
    }
}