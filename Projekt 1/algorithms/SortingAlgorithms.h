#ifndef PROJEKTAIZO_SORTINGALGORITHMS_H
#define PROJEKTAIZO_SORTINGALGORITHMS_H

#include "../utils/Timer.h"
#include <cstdlib>  // rand
#include <random>   // dla std::mt19937 i std::uniform_int_distribution

template<typename T>
class SortingAlgorithms {
private:
    T* arr;
    int algorithm;
    int size;
    int pivot;
    int gap;
    int drunk;

public:
    SortingAlgorithms(T* _arr, int _algorithm, int _size, int _pivot = -1, int _gap = -1, int _drunk = -1);
    ~SortingAlgorithms();

    int sort(Timer& timer);
    int insertionSort(Timer& timer);
    int heapSort(Timer& timer);
    int shellSort(Timer& timer);
    int quickSort(Timer& timer);
    int heapDrunkSort(Timer& timer);

    bool isSorted() const;
    void decrDrunk();

private:
    void heapify(int i, int n);
    void bstify(int i, int n);
    int partition(int low, int high);
    void quickSortRec(int low, int high);
};

template<typename T>
void SortingAlgorithms<T>::decrDrunk() {
    --drunk;
}

template<typename T>
SortingAlgorithms<T>::SortingAlgorithms(T* _arr, int _algorithm, int _size, int _pivot, int _gap, int _drunk)
        : arr(_arr), algorithm(_algorithm), size(_size), pivot(_pivot), gap(_gap), drunk(_drunk) {}

template<typename T>
SortingAlgorithms<T>::~SortingAlgorithms() {}

template<typename T>
int SortingAlgorithms<T>::sort(Timer& timer) {
    switch (algorithm) {
        case 0: return insertionSort(timer);
        case 1: return heapSort(timer);
        case 2: return shellSort(timer);
        case 3: return quickSort(timer);
        case 4: return heapDrunkSort(timer);
        default:
            printf("Wrong number for algorithm\n");
            exit(1);
    }
}

template<typename T>
int SortingAlgorithms<T>::insertionSort(Timer& timer) {
    timer.reset(); timer.start();
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
    timer.stop();
    return timer.result();
}

template<typename T>
void SortingAlgorithms<T>::heapify(int i, int n) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        T temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(largest, n);
    }
}

template<typename T>
void SortingAlgorithms<T>::bstify(int i, int n) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[i]) {
        T temp = arr[i];
        arr[i] = arr[left];
        arr[left] = temp;
        bstify(left, n);
    }
    if (right < n && arr[right] < arr[i]) {
        T temp = arr[i];
        arr[i] = arr[right];
        arr[right] = temp;
        bstify(right, n);
    }
}

template<typename T>
int SortingAlgorithms<T>::heapDrunkSort(Timer& timer) {
    timer.reset(); timer.start();

    for (int i = size / 2 - 1; i >= 0; --i) heapify(i, size);
    for (int end = size - 1; end > 0; --end) {
        T temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;

        if (std::rand() % 10000 < drunk) {
            bstify(0, end);
        } else {
            heapify(0, end);
        }
    }
    timer.stop();
    return timer.result();
}


template<typename T>
int SortingAlgorithms<T>::heapSort(Timer& timer) {
    timer.reset(); timer.start();
    for (int i = size / 2 - 1; i >= 0; --i) heapify(i, size);
    for (int end = size - 1; end > 0; --end) {
        T temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;
        heapify(0, end);
    }
    timer.stop();
    return timer.result();
}

template<typename T>
int SortingAlgorithms<T>::shellSort(Timer& timer) {
    timer.reset(); timer.start();

    if (gap == 0) {
        // Shell 1959: gap = N/2, N/4, ..., 1
        for (int g = size / 2; g > 0; g /= 2) {
            for (int i = g; i < size; ++i) {
                T temp = arr[i];
                int j = i;
                while (j >= g && arr[j - g] > temp) {
                    arr[j] = arr[j - g];
                    j -= g;
                }
                arr[j] = temp;
            }
        }
    } else if (gap == 1) {
        // Frank & Lazarus 1960: gap = 2*(N/2^(k+1)) + 1
        int k = 1;
        while (true) {
            int computedGap = 2 * (size / (1 << (k + 1))) + 1;
            if (computedGap > 1) {
                int g = computedGap;
                for (int i = g; i < size; ++i) {
                    T temp = arr[i];
                    int j = i;
                    while (j >= g && arr[j - g] > temp) {
                        arr[j] = arr[j - g];
                        j -= g;
                    }
                    arr[j] = temp;
                }
                ++k;
            } else {
                break;
            }
        }

        // na końcu gap=1
        int g = 1;
        for (int i = g; i < size; ++i) {
            T temp = arr[i];
            int j = i;
            while (j >= g && arr[j - g] > temp) {
                arr[j] = arr[j - g];
                j -= g;
            }
            arr[j] = temp;
        }
    } else {
        printf("Wrong gap sequence\n");
        exit(1);
    }

    timer.stop();
    return timer.result();
}


template<typename T>
int SortingAlgorithms<T>::partition(int low, int high) {
    T piv;
    if (pivot == 3) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(low, high);
        int randomIndex = dist(rng);
        piv = arr[randomIndex];
    } else if (pivot == 1) {
        piv = arr[low + (high - low) / 2];
    } else if (pivot == 2) {
        T temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
        piv = arr[low];
    } else {
        piv = arr[low];
    }

    int i = low - 1;
    int j = high + 1;
    while (true) {
        do { ++i; } while (arr[i] < piv);
        do { --j; } while (arr[j] > piv);
        if (i >= j) return j;
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

template<typename T>
void SortingAlgorithms<T>::quickSortRec(int low, int high) {
    if (low < high) {
        int p = partition(low, high);
        quickSortRec(low, p);
        quickSortRec(p + 1, high);
    }
}

template<typename T>
int SortingAlgorithms<T>::quickSort(Timer& timer) {
    timer.reset(); timer.start();
    quickSortRec(0, size - 1);
    timer.stop();
    return timer.result();
}

template<typename T>
bool SortingAlgorithms<T>::isSorted() const {
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

#endif // PROJEKTAIZO_SORTINGALGORITHMS_H
