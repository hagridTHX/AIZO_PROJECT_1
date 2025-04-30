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

rem  BADANIE 1:

if false == true (

    rem Wersje podstawowe (Insert, Heap)
    for %%A in (0 1) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test %%A 0 %%S %RUNS% 0 "%OUTPUT_DIR%\bad1_alg%%A.txt"
        )
    )

    rem ShellSort (gap 0 i 1)
    for %%G in (0 1) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 2 0 %%S %RUNS% 0 --gap %%G "%OUTPUT_DIR%\bad1_shell_gap%%G.txt"
        )
    )

    rem QuickSort (pivot 0,1,2,3)
    for %%P in (0 1 2 3) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 3 0 %%S %RUNS% 0 --pivot %%P "%OUTPUT_DIR%\bad1_quick_pivot%%P.txt"
        )
    )

)

rem HeapDrunk (różne wartości drunk)
if false == true (
    for %%D in (1 5 10 20 50) do (
        "%BINARY%" --test 4 0 40000 %RUNS% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
    )
)

if false == true (
    for %%D in (10000) do (
        "%BINARY%" --test 4 0 40000 %RUNS% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
    )
)

if false == true (
    for %%D in (1 5 10 20 50) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 4 0 %%S %RUNS% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
        )
    )
)

if false == true (
    for %%D in (100 300 500 1000) do (
        for %%S in (10000 20000 40000 80000 160000) do (
            "%BINARY%" --test 4 0 %%S %RUN% 0 --drunk %%D "%OUTPUT_DIR%\bad1_heapdrunk_drunk%%D.txt"
        )
    )
)

if false == true (
    for %%A in (0 1) do (
        for %%D in (0 1 2 3 4) do (
            %BINARY% --test %%A 0 80000 %RUNS% %%D %OUTPUT_DIR%\bad2_alg%%A_dist%%D.txt
        )
    )

    REM Shell (gap Franka Lazarusa = 1)
    for %%D in (0 1 2 3 4) do (
        %BINARY% --test 2 0 80000 %RUNS% %%D --gap 1 %OUTPUT_DIR%\bad2_shell_gap1_dist%%D.txt
    )

    REM Quick (pivot środkowy = 1)
    for %%D in (0 1 2 3 4) do (
        %BINARY% --test 3 0 80000 %RUNS% %%D --pivot 1 %OUTPUT_DIR%\bad2_quick_pivot1_dist%%D.txt
    )

    REM HeapDrunk (drunk = 500)
    for %%D in (0 1 2 3 4) do (
        %BINARY% --test 4 0 80000 %RUNS% %%D --drunk 500 %OUTPUT_DIR%\bad2_heapdrunk_drunk500_dist%%D.txt
    )
)

if true == true (
    for %%t in (0 2 3) do (
        %BINARY% --test 3 %%t 80000 %RUNS% 0 --pivot 1 %OUTPUT_DIR%\bad3_quick_type%%t.txt
    )
)

echo.
endlocal
pause
