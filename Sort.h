//
// Created by Alie on 11/9/2020.
//

#ifndef LAB7_RUNTIMEOFSORTS_SORT_H
#define LAB7_RUNTIMEOFSORTS_SORT_H

#include <algorithm>

template<typename T>
struct Sort {
    /**
     * Classic O(n^2) bubble sort
     * @param array to sort
     * @param size  of array
     */
    static void bubble(T *array, int size) {
        for (int i = size - 1; i > 0; i--)
            for (int j = 0; j < i; j++)
                if (array[j] > array[j + 1])
                    std::swap(array[j], array[j + 1]);
    }

    /**
     * Classic O(n^2) selection sort
     * @param array to sort
     * @param size  of array
     */
    static void selection(T *array, int size) {
        for (int i = size - 1; i > 0; i--) {
            int k = 0;
            for (int j = 1; j <= i; j++)
                if (array[j] > array[k])
                    k = j;
            std::swap(array[k], array[i]);
        }
    }

    /**
     * Classic O(n^2) insertion sort
     * @param array to sort
     * @param size  of array
     */
    static void insertion(T *array, int size) {
        for (int i = 1; i <= size - 1; i++)
            for (int j = i - 1; j >= 0 && array[j] > array[j + 1]; j--)
                std::swap(array[j], array[j + 1]);
    }

    /**
     * Classic O(n log n) heap sort.
     * Sort is not stable.
     * @param array to sort
     * @param size  of array
     */
    static void heap(T *array, int size) {
        heapify(array, size);
        for (int heapsize = size; heapsize > 1; heapsize--)
            dequeue(array, heapsize);
    }

    /**
     * Classic O(n log n) merge sort.
     * Space is O(n).
     * Sort is stable and suitable for external sorts.
     * @param array to sort
     * @param size  of array
     */
    // merge step is linear
    // the
    static void merge(T *array, int size) {
        mergesort(array, 0, size - 1);
    }

    /**
     * Classic O(n log n) quicksort.
     * Sort is unstable.
     * Worst case (unusual) is O(n^2).
     * @param array to sort
     * @param size  of array
     */
    static void quick(T *array, int size) {
        quicksort(array, 0, size - 1);
    }

private:
    // quicksort helpers
    static void quicksort(int *a, int lo, int hi) {
        if (hi - lo > 10) {
            int pivotPosition = partition(a, lo, hi); // step 1: pick pivot
            // (linear) ^
            quicksort(a, lo, pivotPosition - 1);
            quicksort(a, pivotPosition + 1, hi);
        } else {
            insertion(a + lo, (hi - lo) + 1); // we call insertion on part of
            // the array, which has size (hi - lo) + 1
            // a + lo is &a[lo]
        }
    }
    static int partition(int *a, int lo, int hi) {
        // Hoare partition scheme
        median3(a, lo, hi);
        int i = lo, j = hi - 1;
        int pivot = a[j]; // as left there by median3
        while (true) {
            while (a[++i] < pivot); // move i forward to first "wrong" value
            while (pivot < a[--j]); // move j backward to first "wrong" value
            if (i >= j)
                break;  // done looking at everything
            std::swap(a[i], a[j]); // swap the two "wrong" values
        }
        std::swap(a[i], a[hi - 1]); // this is where the pivot was stashed by
        // median3, place it in the middle
        return i;
    }
    static void median3(int *a, int lo, int hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] < a[lo])
            std::swap(a[lo], a[mid]);
        if (a[hi] < a[lo])
            std::swap(a[lo], a[hi]);
        if (a[hi] < a[mid])
            std::swap(a[mid], a[hi]);
        // place pivot at postion hi-1
        std::swap(a[mid], a[hi - 1]);
    }

    // merge sort helpers
    static void mergesort(int *array, int lo, int hi) {
        if (hi - lo > 0) {
            int mid = (lo + hi) / 2;
            mergesort(array, lo, mid); // (log n ) / 2
            mergesort(array, mid + 1, hi);
            mergeTwoSorted(array, lo, hi); // linear
        }
    }
    static void mergeTwoSorted(int *a, int lo, int hi) {
        int mid = (lo + hi) / 2;

        // set up temporary scratch space
        int scratchLength = hi - lo + 1;
        int *scratch = new int[scratchLength];
        int k = 0;

        // copy from each as appropriate to scratch
        int i = lo, j = mid + 1;
        while (i <= mid && j <= hi)
            if (a[i] < a[j])
                scratch[k++] = a[i++]; // i is moving bc it was smaller
            else
                scratch[k++] = a[j++]; // j is moving bc it was smaller

        // pick up the remains of whichever one has elements left in it
        while (i <= mid)
            scratch[k++] = a[i++];
        while (j <= hi) // we can do both bc the while will have nothing to
            // do if it's at the end
            scratch[k++] = a[j++];

        // copy back scratch contents to original array
        for (k = 0; k < scratchLength; k++)
            a[lo + k] = scratch[k];

        delete[] scratch; // in production code they have schemes for
        // creating one space to put the extra array and then deleting at the
        // end once
    }

    // heap sort helpers
    static void dequeue(T *array, int size) {
        std::swap(array[0], array[size - 1]); // trick to get dequeue to put
        // max item in correct spot
        percolateDown(array, 0, size - 1); //
    }
    static void heapify(T *array, int size) {
        for (int index = size / 2; index >= 0; index--)
            percolateDown(array, index, size);
    }
    static void percolateDown(T *array, int index, int size) {
        if (hasLeft(index, size)) {
            int child = left(index);
            if (hasRight(index, size)) {
                int r = right(index);
                if (array[r] > array[child])
                    child = r;
            }
            if (array[child] > array[index]) {
                std::swap(array[index], array[child]);
                percolateDown(array, child, size);
            }
        }
    }
    static int parent(int childIndex) {
        return (childIndex - 1) / 2;
    }
    static bool hasLeft(int parentIndex, int size) {
        return left(parentIndex) < size;
    }
    static bool hasRight(int parentIndex, int size) {
        return right(parentIndex) < size;
    }
    static int left(int parentIndex) {
        return parentIndex * 2 + 1;
    }
    static int right(int parentIndex) {
        return left(parentIndex) + 1;
    }

};


#endif //LAB7_RUNTIMEOFSORTS_SORT_H
