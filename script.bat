@echo off
setlocal enabledelayedexpansion

set BINARY=cmake-build-debug\projektAizo.exe

if not exist "%BINARY%" (
    echo Błąd: Brak pliku binarnego w cmake-build-debug. Skompiluj projekt
    exit /b 1
)

set RUNS=100
set OUTPUT_DIR=output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

rem --- BADANIE 1: Wpływ liczebności zbioru ---

if false == true (

    rem --- Wersje podstawowe (Insert, Heap) ---
    for %%A in (0 1) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test %%A 0 %%S %RUNS% 0 "%OUTPUT_DIR%\bad1_alg%%A.txt"
        )
    )

    rem --- ShellSort (gap 0 i 1) ---
    for %%G in (0 1) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 2 0 %%S %RUNS% 0 --gap %%G "%OUTPUT_DIR%\bad1_shell_gap%%G.txt"
        )
    )

    rem --- QuickSort (pivot 0,1,2,3) ---
    for %%P in (0 1 2 3) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 3 0 %%S %RUNS% 0 --pivot %%P "%OUTPUT_DIR%\bad1_quick_pivot%%P.txt"
        )
    )

)

rem --- HeapDrunk (różne wartości drunk) ---
if true == true (
    for %%D in (1 5 10 20 50) do (
        "%BINARY%" --test 4 0 40000 %RUNS% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
    )
)

if true == true (
    for %%D in (1000 2500 5000 7500 10000) do (
        "%BINARY%" --test 4 0 40000 %RUNS% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
    )
)

echo.
endlocal
pause
