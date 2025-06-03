@echo off
setlocal enabledelayedexpansion

set BINARY=cmake-build-debug\projektAizo.exe
set RUNS=50
set OUTPUT_DIR=output

if not exist "%BINARY%" (
    echo Error: Binary file not found. Please build the project.
    exit /b 1
)

if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

rem === GRAPH SIZES ===
set sizes=50 100 200 400 800 1600 3200

rem === DENSITIES ===
set densities=25 50 99

rem === ALGORITHMS:
rem MST - Prim=0, Kruskal=1
rem SHORTEST PATH - Dijkstra=0, Bellman-Ford=1
rem MAX FLOW - Ford-Fulkerson=0

rem === REPRESENTATIONS: 0 - Incidence matrix, 1 - Adjacency list

rem --- MST ---
for %%R in (0 1) do (
    for %%S in (%sizes%) do (
        for %%D in (%densities%) do (
            %BINARY% --test 0 0 %%R %%S %%D %RUNS% mst_prim_r%%R.txt
            %BINARY% --test 0 1 %%R %%S %%D %RUNS% mst_kruskal_r%%R.txt
        )
    )
)

rem --- SHORTEST PATH ---
for %%R in (0 1) do (
    for %%S in (%sizes%) do (
        for %%D in (%densities%) do (
            %BINARY% --test 1 0 %%R %%S %%D %RUNS% sp_dijkstra_r%%R.txt --start 0 --end 10
            %BINARY% --test 1 1 %%R %%S %%D %RUNS% sp_bellman_r%%R.txt --start 0 --end 10
        )
    )
)

rem --- MAX FLOW ---
for %%R in (0 1) do (
    for %%S in (%sizes%) do (
        for %%D in (%densities%) do (
            %BINARY% --test 2 0 %%R %%S %%D %RUNS% flow_r%%R.txt --start 0 --end 10
        )
    )
)

echo.
echo === All tests completed ===
pause
