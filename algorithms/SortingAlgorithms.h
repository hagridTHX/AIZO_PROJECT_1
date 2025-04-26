#ifndef PROJEKTAIZO_SORTINGALGORITHMS_H
#define PROJEKTAIZO_SORTINGALGORITHMS_H

#include "../utils/Timer.h"

// Klasa zawierająca algorytmy sortujące
class SortingAlgorithms {
public:
    // Sortowanie przez wstawianie
    template<typename T>
    static int insertionSort(T arr[], int n, Timer& timer);

    // Sortowanie przez kopcowanie
    template<typename T>
    static int heapSort(T arr[], int n, Timer& timer);

    // Sortowanie Shella
    //gapMethod: 0 - Shell 1959, 1 - Frank & Lazarus 1960
    template<typename T>
    static int shellSort(T arr[], int n, int gapMethod, Timer& timer);

    // Quicksort
    //positionType: 0 - pierwszy, 1 - środkowy, 2 - ostatni, 3 - losowy
    template<typename T>
    static int quickSort(T arr[], int n, int pivotType, Timer& timer);

    // HeapDrunkSort (p w promilach: 0–1000)
    template<typename T>
    static int heapDrunkSort(T arr[], int n, int p, Timer& timer);

    template<typename T>
    static bool isSorted(const T arr[], int n);

private:
    // Pomocnicze metody
    template<typename T>
    static void siftDown(T arr[], int i, int n);

    template<typename T>
    static int partition(T arr[], int low, int high, int pivotType);

    template<typename T>
    static void quickSortRec(T arr[], int low, int high, int pivotType);
};

#endif