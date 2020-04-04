#include "Union.h"

Union::Union(int n) {
    //Initialize the Union object and create n amount of nodes
    this -> total_sets = n;
    this -> sets = (Node **) malloc(n*sizeof(Node *));
    this -> finalized = false;
    //initialize all the nodes to -1
    for(int i = 1; i <= n; i++) {
        this -> sets[i - 1] = new Node(-1);
    }
}

void Union::make_set(int i) {
    //if finalized, or -1, do nothing
    if(finalized || this -> sets[i - 1] -> getMember() != -1) return;
    //I is out of range for the objects so a new set needs to be made 
    if(i > this -> total_sets) {
        this -> total_sets += 1;
        //dynamically allocate new complete set of size+1
        Node **tmpSets = (Node **) malloc(this -> total_sets*sizeof(Node *));
        //copy over old set
        memcpy(tmpSets, this -> sets, (this->total_sets - 1)*sizeof(Node *));
        //create the new node initialized to i
        this -> sets[this -> total_sets - 1] = new Node(i);
        return;
    }
    else {
        this -> sets[i - 1] = new Node(i);
    }
    
}

//Creates the Union of two sets
void Union::union_sets(int i, int j) {
    // printf("Creating union %d, %d\n", i, j);
    if(finalized) return;
    return Link(find_set(i), find_set(j));
}

//Finds the set an object belongs too, whether it be itself or another set
int Union::find_set(int i) {
    if(this -> sets[i - 1] -> getMember() == -1) 
        return -1;
    if(this -> sets[i - 1] -> getParent() == i) 
        return i;
    else {
        int parent = find_set(this->sets[i-1] -> getParent());
        this -> sets[i - 1] -> setParent(parent);
        return parent;
    }

}

//Finalizes the sets and extracts the disjoint images
//returns the amount of representatives (disjoint sets) and updates the
//object to store only those sets
int Union::final_sets() {
    this -> finalized = true;
    int *final_sets = new int[this -> total_sets];

    int representatives = 0;
    
    //Only set objects with themselves as parents are representatives
    //We store their indices in a temporary array
    //Set the index of the repr as its parent 
    for(int i = 0; i < this -> total_sets; i++) {
        if(this -> sets[i] -> getMember() != -1) {
            if( this -> sets[i] -> getParent() == (i + 1)) {
                final_sets[representatives] = i+1;
                this -> sets[i] -> setParent(representatives);
                representatives += 1;
            }
            
        }
        
    }
    

    for(int k = 0; k < representatives; k++)
        for(int i = 0; i < this -> total_sets; i++) {
            if(this -> sets[i] -> getParent() == final_sets[k] ) {
                this -> sets[i] -> setParent(k); //set the parent to the new representative
            }
        }

    // //Allocate a new set to hold just the reps
    // Node ** newSet = (Node **) malloc(representatives*sizeof(Node *));

    // //gets the Node objects from the current set using the indices of reps
    // //that we stored earlier
    // for(int j = 0; j < representatives; j++) {
    //     newSet[j] = this -> sets[final_sets[j] - 1];
    //     newSet[j] -> setParent(j);
    // }
    //updates the total sets and the set pointer to the new set
    // this -> total_sets = representatives;
    // this -> sets = newSet;

    delete [] final_sets;
    return representatives;
}


void Union::Link(int x, int y) {
    //either x or y are not initialized or they are the same
    if(x < 0 ||y < 0 || x == y) return;

    //get the two root Nodes for these sets
    Node *xNode = this -> sets[x - 1];
    Node *yNode = this -> sets[y - 1];
    //combine their total sizes
    int newSize = yNode -> getSize() + xNode -> getSize();
    //Link the two sets together and update the new root to the new size
    if(xNode -> getRank() > yNode -> getRank()) {
        yNode -> setParent(x);
        xNode -> setSize(newSize);
    }
    else if(yNode -> getRank() > xNode -> getRank()) {  
        xNode -> setParent(y);
        yNode -> setSize(newSize);
    }
    else if(x != y) {
        yNode -> setParent(x);
        xNode -> setRank(xNode -> getRank() + 1);
        xNode -> setSize(newSize);
    }
}

//returns the set object
Node **Union::getSet() {
    return this -> sets;
}

//returns the total number of sets
int Union::getSize() {
    return this -> total_sets;
}