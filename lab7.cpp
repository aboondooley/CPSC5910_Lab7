//
// Created by Alie Boon-Dooley on 11/9/2020.
// Seattle University CPSC 5910
// Lab 7 Runtime of Sorts
//

#include <iostream>
#include "RandomArray.h"
#include "Sort.h"
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

/**
 * Times the different sort functions so the user can see how long each sort
 * function takes to sort n number of elements
 * @param r a RandomArray object full of random ints to sort
 * @param fx the sort function to test, it must be void and take two
 * parameters, one int array and an int
 * @return returns the number of milliseconds the sort took to complete
 */
milliseconds timer(RandomArray &r, std::function<void(int*, int)> fx) {
    high_resolution_clock::time_point start, end;
    milliseconds ms;

    start = high_resolution_clock::now();
    fx(r.array, r.size);
    end = high_resolution_clock::now();
    ms = duration_cast<milliseconds>(end - start);
    return ms;
}

/**
 * Does the printing for each test, reporting the sort function name and the
 * elapsed time to sort
 * @param title name of the sort function
 * @param r RandomArray object to sort
 * @param fx the particular sort function to call
 */
void printTests(string title, RandomArray &r,
                std::function<void(int*, int)> fx) {
    cout << title << " elapsed time: " <<
         timer(r, fx).count() << "ms" << endl;
}

/**
 * Tests *almost* all of the sorts to for their time efficiency as n doubles.
 * Reshuffles the RandomArray between each sort
 * @param n the size of array to test
 */
void testAllSorts(int n) {
    RandomArray r(n);

    cout << "sorting " << n << " values:" << endl;
    printTests("merge sort", r, Sort<int>::merge);
    r.shuffle();
    printTests("heap sort", r, Sort<int>::heap);
    r.shuffle();
    printTests("quicksort", r, Sort<int>::quick);
    r.shuffle();
    if (n <= 320000){ // only test if n is less than or equal to 320000
        printTests("insertion sort", r, Sort<int>::insertion);
    }
}

/**
 * This function unfortunately had to be created because the std::sort()
 * function takes different parameters than the other functions and could not
 * be called using the timer() function.
 * It creates the RandomArray, does the printing, testing, and timing for
 * introspection sort
 * @param n the size of the array to test
 */
void testIntrospection(int n) {
    RandomArray r(n);
    cout << "introspection sort elapsed time: ";
    high_resolution_clock::time_point start, end;
    milliseconds ms;

    start = high_resolution_clock::now();
    std::sort(r.array, r.array + r.size);
    end = high_resolution_clock::now();
    ms = duration_cast<milliseconds>(end - start);
    cout << ms.count() << "ms" << endl;
}

/**
 * Main entry point for testing all of the sorting for time efficiency
 * @return 0 if successful
 */
int main() {

    for (int n = 40000; n <= 20480000; n*=2) {
        testAllSorts(n);
        testIntrospection(n); // introsort is tested last
        cout << endl;
    }


    return EXIT_SUCCESS;
}

// Resources:
// I used this post to learn how to pass a function as an argument
// https://stackoverflow.com/questions/16111285/how-to-pass-and-execute-anonymous-function-as-parameter-in-c11
// and this for how to call std::sort()
// https://www.geeksforgeeks.org/sort-c-stl/