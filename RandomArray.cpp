//
// Created by Alie on 11/9/2020.
//

#include "RandomArray.h"
#include <random>
#include <sstream>

using namespace std;

random_device RandomArray::seeder;
mt19937 RandomArray::generator(seeder());

int RandomArray::random() const {
    /* Use a distribution to transform the random unsigned int generated by
     * RandomArray::generator into an int in the desired range.
     */
    std::uniform_int_distribution<int> distribution(0, size - 1);
    return distribution(generator);
}

RandomArray::RandomArray(int sz) {
    size = sz;
    array = new int[size];
    for (int i = 0; i < size; i++)
        array[i] = random();
}

bool RandomArray::isSorted() const {
    for (int i = 1; i < size; i++)
        if (array[i] < array[i - 1])
            return false;
    return true;
}

void RandomArray::shuffle() {
    for (int i = 0; i < size; i++)
        swap(array[i], array[random()]);
}

std::string RandomArray::toString() const {
    ostringstream ss;
    if (size > 20) {
        for (int i = 0; i < 10; i++)
            ss << array[i] << ' ';
        ss << "... ";
        for (int i = size - 10; i < size; i++)
            ss << array[i] << ' ';
    } else {
        for (int i = 0; i < size; i++)
            ss << array[i] << ' ';
    }
    return ss.str();
}

RandomArray::~RandomArray() {
    delete[] array;
}
