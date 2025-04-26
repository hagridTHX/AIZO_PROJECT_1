#include "SortingAlgorithms.h"
#include <cstdlib> // rand

// insertionSort
template<typename T>
int SortingAlgorithms::insertionSort(T arr[], int n, Timer& timer) {
    timer.reset(); timer.start();
    for(int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
    timer.stop();
    return timer.result();
}

// siftDown - inline obliczenie dzieci kopca
template<typename T>
void SortingAlgorithms::siftDown(T arr[], int i, int n) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < n && arr[l] > arr[largest]) largest = l;
    if(r < n && arr[r] > arr[largest]) largest = r;
    if(largest != i) {
        T tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        siftDown(arr, largest, n);
    }
}

// heapSort
template<typename T>
int SortingAlgorithms::heapSort(T arr[], int n, Timer& timer) {
    timer.reset(); timer.start();
    for(int i = n / 2 - 1; i >= 0; --i) siftDown(arr, i, n);
    for(int end = n - 1; end > 0; --end) {
        T tmp = arr[0]; arr[0] = arr[end]; arr[end] = tmp;
        siftDown(arr, 0, end);
    }
    timer.stop();
    return timer.result();
}

// shellSort
template<typename T>
int SortingAlgorithms::shellSort(T arr[], int n, int gapMethod, Timer& timer) {
    timer.reset(); timer.start();
    int gap = (gapMethod == 1 ? 1 : n / 2);
    if(gapMethod == 1) while(gap < n) gap = 3 * gap + 1;
    for(; gap > 0; gap = (gapMethod == 1 ? gap / 3 : gap / 2)) {
        for(int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j = i;
            while(j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
    timer.stop();
    return timer.result();
}

// partition
template<typename T>
int SortingAlgorithms::partition(T arr[], int low, int high, int pivotType) {
    T pivot;
    switch(pivotType) {
        case 1: pivot = arr[low + (high - low) / 2]; break;
        case 2: pivot = arr[high]; break;
        case 3: pivot = arr[low + std::rand() % (high - low + 1)]; break;
        default: pivot = arr[low];
    }
    int i = low - 1;
    int j = high + 1;
    while(true) {
        do { ++i; } while(arr[i] < pivot);
        do { --j; } while(arr[j] > pivot);
        if(i >= j) return j;
        T tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
}

// quickSortRec
template<typename T>
void SortingAlgorithms::quickSortRec(T arr[], int low, int high, int pivotType) {
    if(low < high) {
        int p = partition(arr, low, high, pivotType);
        quickSortRec(arr, low, p, pivotType);
        quickSortRec(arr, p + 1, high, pivotType);
    }
}

// quickSort
template<typename T>
int SortingAlgorithms::quickSort(T arr[], int n, int pivotType, Timer& timer) {
    timer.reset(); timer.start();
    quickSortRec(arr, 0, n - 1, pivotType);
    timer.stop();
    return timer.result();
}

// heapDrunkSort
template<typename T>
int SortingAlgorithms::heapDrunkSort(T arr[], int n, int p, Timer& timer) {
    timer.reset(); timer.start();
    for(int i = n / 2 - 1; i >= 0; --i) siftDown(arr, i, n);
    for(int end = n - 1; end > 0; --end) {
        T tmp = arr[0]; arr[0] = arr[end]; arr[end] = tmp;
        if(std::rand() % 1000 < p) {
            int i1 = std::rand() % n;
            int i2 = std::rand() % n;
            T tmp2 = arr[i1]; arr[i1] = arr[i2]; arr[i2] = tmp2;
        }
        siftDown(arr, 0, end);
    }
    timer.stop();
    return timer.result();
}

template<typename T>
bool SortingAlgorithms::isSorted(const T arr[], int n) {
    for(int i = 1; i < n; ++i) {
        if(arr[i-1] > arr[i]) return false;
    }
    return true;
}
