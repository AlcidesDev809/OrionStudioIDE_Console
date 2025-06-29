@echo off
set SOURCES=src\*.c
set INCLUDES=include\*.h

if "%1"=="clean" (
  
  if "%2"=="all" (
    del /Q %SOURCES% 2>nul
    del /Q %INCLUDES% 2>nul
    del /Q build\*.o 2>nul
    del /Q build\*.exe 2>nul
    exit /b 0
  )
  
  del /Q build\*.o 2>nul
  del /Q build\*.exe 2>nul
  exit /b 0
)

if not exist build (
  mkdir build
)

for %%f in (%SOURCES%) do (
  gcc -Iinclude -Wall -Wextra -std=c11 %%f -c -o build\%%~nf.o
)

gcc build\*.o -o build\orionConsole.exe

if not exist build\orionConsole.exe (
  echo Program compilation failed
  ) else (
  echo Program compiled successfully
)
