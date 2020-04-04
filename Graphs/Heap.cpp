#include "Heap.hpp"

Heap::Heap(float keys[], int n) : length(n) {
    //indices go from 0 to n-1
    this -> keys = new float[n + 1];
    //indices go from 0 to 2*n - 2
    //H[n - 1, ..., 2n - 2] store the indices of keys
    //H[0, ..., n - 2] store the order of the indices
    this -> heap = new int[2*n - 1];
    //Elements removed from heap are given index 0
    //since this is a min heap, the largest possible value is +INF
    this -> keys[0] = INFINITY;
    //copy over the keys
    for(int j = 1; j < n + 1; j++) 
        this -> keys[j] = keys[j - 1];
    //Initialize H[n-1]-H[2n-2] with 1, 2, 3, ..., n
    for(int i = n-1; i < 2*n-1; i++) 
        this -> heap[i] = i - n + 2;
    //Create the heap of the indices for the internal nodes
    for(int k = n - 2; k >= 0; k--) {
        if(this -> keys[heap[2*k + 1]] < this -> keys[heap[2*k + 2]])
            this -> heap[k] = this -> heap[2*k + 1];
        else 
            this -> heap[k] = this -> heap[2*k + 2];
    }
}

//Checks whether a index is in the heap
//param id: Index of the key
bool Heap::in_heap(int id) {
    return (heap[length + id - 2] == id);
}

//Returns the minimum key 
float Heap::min_key() {
    return keys[heap[0]];
}

//Returns the id in the heap (First element) with the minimum key
int Heap::min_id() {
    return heap[0];
}

//Return the key of id
//param id: Index of the key
float Heap::key(int id) {
    return keys[id];
}

void Heap::delete_min() {
    //set the last index of the min value to 0
    //keys[0] is always infinity (largest possible value)
    heap[heap[0] + length - 2] = 0;
    //Index of the parent of the last index, also stores min_id
    int index = (int) floor((double) (heap[0] + length - 3)/2);
    while(index >= 0) {
        int left = 2*index + 1;
        int right = 2*index + 2;
        //replace instances of min_id, with the smallest of its children
        if(keys[heap[left]] < keys[heap[right]])
            heap[index] = heap[left];
        else
            heap[index] = heap[right];

        index = (int) floor((double) (index - 1) / 2);
    }
}

//Sets the key at id to new_key if new_key is less than the old key
//param id: index of the param to update
//param new_key: new value of the key
void Heap::decrease_key(int id, float new_key) {
    //get the old key from keys
    float old_key = keys[id];
    
    if(old_key > new_key) {
        //update the key
        keys[id] = new_key;
        //Check if the heap property has been violated and fix it
        int index = (int) floor((double) (id + length - 3) / 2);
        while(index >= 0) {
            int left = 2*index + 1;
            int right = 2*index + 2;
            
            if(keys[heap[left]] < keys[heap[right]])
                heap[index] = heap[left];
            else
                heap[index] = heap[right];
            index = (int) floor((double) (index - 1) / 2);

        }
    }
}

//Checks if the heap is empty
//Returns true if all the indices are 0 (Removed)
bool Heap::is_empty() {
    for(int i = 0; i < 2*length - 1; i++)
        if(heap[i] != 0) return false;

    return true;
}

//Helper print function for debugging
void Heap::print() {
    cout << "Printing Original Items" <<endl;
    for(int i = 0; i < length+1; i++) {
        cout << keys[i] << " ";
    }
    cout << endl;
    for(int j = 0; j < 2*length - 1; j++) {
        cout << heap[j] << " ";
    }
    cout << endl;
}