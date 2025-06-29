#include <windows.h>
#include <shobjidl.h>
#include <stdio.h>

#include "file.h"

void getFilePath(char *buffer)
{
    SetProcessDPIAware();

    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen = NULL;

        hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                              &IID_IFileOpenDialog, (void **)&pFileOpen);

        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            pFileOpen->lpVtbl->GetOptions(pFileOpen, &dwOptions);
            pFileOpen->lpVtbl->SetOptions(pFileOpen, dwOptions | FOS_FILEMUSTEXIST);

            hr = pFileOpen->lpVtbl->Show(pFileOpen, NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->lpVtbl->GetResult(pFileOpen, &pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    pItem->lpVtbl->GetDisplayName(pItem, SIGDN_FILESYSPATH, &pszFilePath);

                    char path[1024];
                    wcstombs(path, pszFilePath, sizeof(path));
                    strcpy(buffer, path);

                    CoTaskMemFree(pszFilePath);
                    pItem->lpVtbl->Release(pItem);
                }
            }
            pFileOpen->lpVtbl->Release(pFileOpen);
        }
        CoUninitialize();
    }

    fflush(stdout);
    fflush(stdin);
}