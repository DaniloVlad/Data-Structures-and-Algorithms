#ifndef _Heap
#define _Heap

#include <iostream>
#include <math.h>
using namespace std;


class Heap {
    public:
        Heap(float keys[], int n);
        bool in_heap(int id);
        float min_key();
        int min_id();
        float key(int id);
        void delete_min();
        void decrease_key(int id, float new_key);
        bool is_empty();
        void print();
    private:
        //keys stores the values of the heap in original order
        float *keys;
        //heap of indices of keys
        int *heap;
        int length;
};

#endif