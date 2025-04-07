#ifndef PROJEKTAIZO_DATA_H
#define PROJEKTAIZO_DATA_H

class DataGenerator {
public:
    // Generuje tablicę int o rozmiarze n według rozkładu:
    // 0 - losowy, 1 - rosnący, 2 - malejący, 3 - częściowo posortowany (33%), 4 - częściowo posortowany (66%)
    static int* generateIntData(int n, int distType);

    // Generuje tablicę float o rozmiarze n według podanego rozkładu.
    static float* generateFloatData(int n, int distType);

    // Generuje tablicę char o rozmiarze n według podanego rozkładu.
    static char* generateCharData(int n, int distType);
};

#endif //PROJEKTAIZO_DATA_H
