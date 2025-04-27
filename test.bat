@echo off
setlocal enabledelayedexpansion

set BINARY=cmake-build-debug\projektAizo.exe
set OUTPUT_DIR=output
set OUTPUT_FILE=test.txt
set RUNS=100

if not exist "%BINARY%" (
    echo Błąd: Brak pliku binarnego w cmake-build-debug. Skompiluj projekt!
    exit /b 1
)

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

rem --- Badanie "pijanego studenta" (drunk 0,1,2,5,10,15,...50) ---
set TYPE=0
set ALGORITHM=4

for %%S in (10000 20000 40000 80000 160000) do (
    for %%D in (0 1 2 3 4 5 10) do (
        echo Testowanie: size=%%S drunk=%%D
        "%BINARY%" --test %ALGORITHM% %TYPE% %%S %RUNS% --drunk %%D --distribution 0 "%OUTPUT_DIR%\%OUTPUT_FILE%"
    )
)

echo.
echo Wszystkie testy pijanego studenta zakończone. Wyniki są w "%OUTPUT_DIR%\%OUTPUT_FILE%"

endlocal
pause
