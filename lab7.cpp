#include <iostream>
#include "RandomArray.h"
#include "Sort.h"
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

void printAndTest(string title, RandomArray &ra) {
    cout << title << ": "
         << ra.toString()
         << (ra.isSorted() ? "" : "not " ) << "sorted"
         << endl;
}

milliseconds timer(RandomArray &r, std::function<void(int*, int)> fx) {
    high_resolution_clock::time_point start, end;
    milliseconds ms;

    start = high_resolution_clock::now();
    fx(r.array, r.size);
    end = high_resolution_clock::now();
    ms = duration_cast<milliseconds>(end - start);
    return ms;
}

void printTests(string title, RandomArray &r,
                std::function<void(int*, int)> fx) {
    cout << title << " elapsed time: " <<
         timer(r, fx).count() << "ms" << endl;
}

void testAllSorts(int n) {
    RandomArray r(n);

    cout << "sorting " << n << " values:" << endl;
    printTests("quicksort", r, Sort<int>::quick);
    r.shuffle();
    printTests("heap sort", r, Sort<int>::heap);
    r.shuffle();
    printTests("merge sort", r, Sort<int>::merge);
    r.shuffle();
    if (n <= 320000){
        printTests("insertion sort", r, Sort<int>::insertion);
        cout << endl;
    }
}


int main() {

    for (int n = 40000; n < 20480000; n*=2) {
        testAllSorts(n);
    }



    /*
     * RandomArray x(20000);
    printAndTest("a random array  ", x);

    // quicksort
    cout << endl;
    Sort<int>::quick(x.array, x.size);
    printAndTest("quicksorted     ", x);
    Sort<int>::quick(x.array, x.size);
    printAndTest("sort of sorted  ", x);
    x.shuffle();
    printAndTest("reshuffled      ", x);

    // merge sort
    cout << endl;
    Sort<int>::merge(x.array, x.size);
    printAndTest("merge sorted    ", x);
    Sort<int>::merge(x.array, x.size);
    printAndTest("sort of sorted  ", x);
    x.shuffle();
    printAndTest("reshuffled      ", x);

    // heap sort
    cout << endl;
    Sort<int>::heap(x.array, x.size);
    printAndTest("heap sorted     ", x);
    Sort<int>::heap(x.array, x.size);
    printAndTest("sort of sorted  ", x);
    x.shuffle();
    printAndTest("reshuffled      ", x);

    // insertion sort
    // if we increase the size by 10, we increase the time by 100
    cout << endl;
    Sort<int>::insertion(x.array, x.size);
    printAndTest("insertion sorted", x);
    Sort<int>::insertion(x.array, x.size);
    printAndTest("sort of sorted  ", x);
    x.shuffle();
    printAndTest("reshuffled      ", x);

    // selection sort
    cout << endl;
    Sort<int>::selection(x.array, x.size);
    printAndTest("selection sorted", x);
    x.shuffle();
    printAndTest("reshuffled      ", x);

    // bubble sort
    cout << endl;
    Sort<int>::bubble(x.array, x.size);
    printAndTest("bubble sorted   ", x);
     */

    return EXIT_SUCCESS;
}
