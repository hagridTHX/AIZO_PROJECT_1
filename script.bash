# Sprawdzamy, czy plik binarny istnieje w cmake-build-debug
BINARY="./cmake-build-debug/projektAizo"
if [ ! -f "$BINARY" ]; then
    echo "Błąd: Nie znaleziono skompilowanego pliku binarnego w cmake-build-debug."
    echo "Upewnij się, że projekt został skompilowany."
    exit 1
fi

echo "=== Testy programu projektAizo ==="

# 1) HELP MODE
echo -e "\n[1] HELP MODE"
$BINARY --help

# 2) FILE TEST MODE - InsertSort (algorithm=0), typ int (type=0)
echo -e "\n[2] FILE TEST MODE - InsertSort (algorithm=0, type=0)"
$BINARY --file 0 0 input/intData.txt output/intDataSorted.txt

# 3) FILE TEST MODE - QuickSort (algorithm=3), typ float (type=1), pivot=2
echo -e "\n[3] FILE TEST MODE - QuickSort (algorithm=3, type=1, pivot=2)"
$BINARY --file 3 1 --pivot 2 input/floats.txt

# 4) FILE TEST MODE - InsertDrunk (algorithm=4), typ boardGame (type=3), drunk=5
echo -e "\n[4] FILE TEST MODE - InsertDrunk (algorithm=4, type=3, drunk=5)"
$BINARY --file 4 3 --drunk 5 input/boardgames.txt output/boardgamesOut.txt

# 5) BENCHMARK MODE - InsertSort (algorithm=0), typ int (type=0), distribution=0, runs=100
echo -e "\n[5] BENCHMARK MODE - InsertSort (algorithm=0, type=0, distribution=0, runs=100)"
$BINARY --test 0 0 --distribution 0 --runs 100

# 6) BENCHMARK MODE - QuickSort (algorithm=3), typ float (type=1), pivot=3, distribution=2, runs=50
echo -e "\n[6] BENCHMARK MODE - QuickSort (algorithm=3, type=1, pivot=3, distribution=2, runs=50)"
$BINARY --test 3 1 --pivot 3 --distribution 2 --runs 50 output/bench_floats.txt

# 7) BENCHMARK MODE - ShellSort (algorithm=2), typ tablica char[] (type=2), gap=1, distribution=4, runs=30
echo -e "\n[7] BENCHMARK MODE - ShellSort (algorithm=2, type=2, gap=1, distribution=4, runs=30)"
$BINARY --test 2 2 --gap 1 --distribution 4 --runs 30 output/bench_strings.txt

echo -e "\nWykonano wszystkie testy."
