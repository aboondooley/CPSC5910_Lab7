//
// Created by Alie on 11/9/2020.
//

#ifndef LAB7_RUNTIMEOFSORTS_RANDOMARRAY_H
#define LAB7_RUNTIMEOFSORTS_RANDOMARRAY_H

#include <string>
#include <random>

class RandomArray {
public:
    int *array;
    int size;

    RandomArray(int size = 100);
    ~RandomArray();
    RandomArray(const RandomArray &) = delete;
    RandomArray &operator=(const RandomArray &) = delete;

    bool isSorted() const;
    void shuffle();
    std::string toString() const;

private:
    /**
     * Used to obtain a seed for the random number engine.
     */
    static std::random_device seeder;

    /**
     * Standard mersenne_twister_engine (seeded with RandomArray::seeder).
     */
    static std::mt19937 generator;

    int random() const;
};


#endif //LAB7_RUNTIMEOFSORTS_RANDOMARRAY_H
