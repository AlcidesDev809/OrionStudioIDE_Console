@echo off
set SOURCES=src\*.c
set INCLUDES=include\*.h
set BUILD=build
set PROGRAM_NAME=orionConsole.exe

if "%1"=="run" (
  start %BUILD%\%PROGRAM_NAME%
  exit /b 0
)

if "%1"=="clean" (
  
  if "%2"=="all" (
    del /Q %SOURCES% 2>nul
    del /Q %INCLUDES% 2>nul
    del /Q %BUILD%\*.o 2>nul
    del /Q %BUILD%\*.exe 2>nul
    exit /b 0
  )
  
  del /Q %BUILD%\*.o 2>nul
  del /Q %BUILD%\*.exe 2>nul
  exit /b 0
)

if not exist %BUILD% (
  mkdir %BUILD%
)

for %%f in (%SOURCES%) do (
  gcc -Iinclude -Wall -Wextra -std=c11 %%f -c -o %BUILD%\%%~nf.o
)

gcc %BUILD%\*.o -o %BUILD%\%PROGRAM_NAME% -lole32 -lshell32 -luuid

if not exist %BUILD%\%PROGRAM_NAME% (
  echo Program compilation failed
  ) else (
  echo Program compiled successfully
)
