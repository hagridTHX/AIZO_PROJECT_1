@echo off
setlocal enabledelayedexpansion

set BINARY=cmake-build-debug\projektAizo.exe

if not exist "%BINARY%" (
    echo Błąd: Brak pliku binarnego w cmake-build-debug. Skompiluj projekt!
    exit /b 1
)

rem --- Tworzymy folder output jeśli nie istnieje ---
if not exist "output" mkdir "output"

rem --- Stare testy (nieaktywne) ---
if true == true (

    rem QuickSort (pivot = środkowy element)
    "%BINARY%" --file 3 0 inputData.txt --pivot 1

    rem ShellSort (gap = metoda Shell'a 1959)
    "%BINARY%" --file 2 1 floatData.txt --gap 0

    rem HeapDrunk (50% szansa na zaburzenie)
    "%BINARY%" --file 4 2 myChars.txt --drunk 9999

    rem QuickSort (pivot losowy, własny output)
    "%BINARY%" --file 3 0 myInts.txt mySortedInts.txt --pivot 3

    rem HeapSort (bez dodatkowych opcji)
    "%BINARY%" --file 1 3 myBoardGames.txt

    rem --- NOWE TESTY dla char[] ---

    rem InsertSort (dla charów)
    "%BINARY%" --file 0 2 myChars.txt insert.txt

    rem HeapSort (dla charów)
    "%BINARY%" --file 1 2 myChars.txt heap.txt

    rem ShellSort (gap = Shell 1959)
    "%BINARY%" --file 2 2 myChars.txt  shell0.txt --gap 0

    rem ShellSort (gap = Frank i Lazarus 1960)
    "%BINARY%" --file 2 2 myChars.txt shell1.txt --gap 1

    rem QuickSort (pivot = pierwszy element)
    "%BINARY%" --file 3 2 myChars.txt quick0.txt --pivot 0

    rem QuickSort (pivot = środkowy element)
    "%BINARY%" --file 3 2 myChars.txt quick1.txt --pivot 1

    rem QuickSort (pivot = ostatni element)
    "%BINARY%" --file 3 2 myChars.txt quick2.txt --pivot 2

    rem QuickSort (pivot = losowy element)
    "%BINARY%" --file 3 2 myChars.txt quick3.txt --pivot 3

    rem HeapDrunkSort (drunk = 0, bez zaburzeń)
    "%BINARY%" --file 4 2 myChars.txt drunk0.txt --drunk 0
)

rem HeapDrunkSort (drunk = 0, bez zaburzeń)
"%BINARY%" --file 4 2 myChars.txt drunk9999.txt --drunk 10

echo.
echo Wszystkie testy FILE TEST MODE na CHARACH zakończone. Wyniki są zapisane w folderze output.

endlocal
pause
