#ifndef PROJEKTAIZO_DATA_H
#define PROJEKTAIZO_DATA_H

class DataGenerator {
public:

    static int* generateIntData(int n, int distType);
    static float* generateFloatData(int n, int distType);
    static char* generateCharData(int n, int distType);
};

#endif //PROJEKTAIZO_DATA_H
