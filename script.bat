@echo off
setlocal enabledelayedexpansion

set BINARY=cmake-build-debug\projektAizo.exe

if not exist "%BINARY%" (
    echo Błąd: Brak pliku binarnego w cmake-build-debug. Skompiluj projekt!
    exit /b 1
)

set RUNS=100
set OUTPUT_DIR=output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

rem --- BADANIE 1: Wpływ wielkości danych ---
for %%A in (0 1 2 3) do (
    for %%S in (10000 20000 40000 80000 160000) do (
        if "%%A"=="2" (
            for %%G in (0 1) do (
                "%BINARY%" --test %%A 0 %%S %RUNS% --gap %%G --distribution 0 "%OUTPUT_DIR%\bad1_alg%%A_size%%S_gap%%G.txt"
            )
        ) else if "%%A"=="3" (
            for %%P in (0 1 2 3) do (
                "%BINARY%" --test %%A 0 %%S %RUNS% --pivot %%P --distribution 0 "%OUTPUT_DIR%\bad1_alg%%A_size%%S_pivot%%P.txt"
            )
        ) else (
            "%BINARY%" --test %%A 0 %%S %RUNS% --distribution 0 "%OUTPUT_DIR%\bad1_alg%%A_size%%S.txt"
        )
    )
)

rem --- BADANIE 1b: "Pijany student" ---
for %%S in (10000 20000 40000 80000 160000) do (
    for %%D in (0 250 500 750 1000) do (
        "%BINARY%" --test 4 0 %%S %RUNS% --drunk %%D --distribution 0 "%OUTPUT_DIR%\bad1_drunk_size%%S_drunk%%D.txt"
    )
)

rem --- BADANIE 2: Rozkład początkowy ---
set SELECTED_SIZE=40000
for %%A in (0 1 2 3) do (
    for %%D in (0 1 2 3 4) do (
        if "%%A"=="2" (
            "%BINARY%" --test %%A 0 %SELECTED_SIZE% %RUNS% --gap 1 --distribution %%D "%OUTPUT_DIR%\bad2_alg%%A_dist%%D.txt"
        ) else if "%%A"=="3" (
            "%BINARY%" --test %%A 0 %SELECTED_SIZE% %RUNS% --pivot 3 --distribution %%D "%OUTPUT_DIR%\bad2_alg%%A_dist%%D.txt"
        ) else (
            "%BINARY%" --test %%A 0 %SELECTED_SIZE% %RUNS% --distribution %%D "%OUTPUT_DIR%\bad2_alg%%A_dist%%D.txt"
        )
    )
)

rem --- BADANIE 2b: "Pijany student" przy różnych rozkładach ---
for %%D in (0 1 2 3 4) do (
    "%BINARY%" --test 4 0 %SELECTED_SIZE% %RUNS% --drunk 500 --distribution %%D "%OUTPUT_DIR%\bad2_drunk_dist%%D.txt"
)

rem --- BADANIE 3: Typ danych ---
set ALG_CHOSEN=3
set PIVOT_CHOSEN=3

for %%T in (0 1 2 3) do (
    "%BINARY%" --test %ALG_CHOSEN% %%T %SELECTED_SIZE% %RUNS% --pivot %PIVOT_CHOSEN% --distribution 0 "%OUTPUT_DIR%\bad3_type%%T.txt"
)

echo.
echo Wszystkie badania zakończone. Wyniki są w folderze "%OUTPUT_DIR%"

endlocal
pause
