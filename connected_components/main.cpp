#include <iostream>
#include <string>
#include "Union.h"


int main() {
    char prevLine[100] = {0};
    char nextLine[100] = {0};
    int line = 0;

    //count is used to ensure that the sum of the sizes of components is equal to the
    //amount of + in the file
    int count = 0;

    //create the union bucket for every pixel, all nodes are initialized to -1
    Union * uandf = new Union(71*71);

    fgets(prevLine, 100, stdin);
    //remove one since each line has a \n at the end
    int len = (int) strlen(prevLine) - 1;

    //creates the sets for the first line
    //sets will have indices 1,...,71
    for(int i = 0; i < len; i++) {
        //we need to initialize the set for this index
        if(prevLine[i] == '+') {
            uandf -> make_set(i + 1);
            count += 1;    
        }
        if(i >= 1 && uandf -> find_set(i) != -1) uandf -> union_sets(i, i+1);
    }

    //output the first line
    printf("%s", prevLine);

    //Loop through each line, and sets prevLine = nextLine after each iteration
    while(fgets(nextLine, 100, stdin) != NULL) {
        //increment the current line count and line length
        line+=1;
        len = strlen(nextLine) - 1;

        //output the line
        printf("%s", nextLine);

        for(int k = 0; k < len; k++) {
            //initializes the set for index k and checks if it is connected to an object
            //beside it or above it
            if(nextLine[k] == '+') {
                //creates the set for i = (k + 1) + ((current line offset -1)*line length)
                //ie the first object in line 2 has index 0 + 1 + 1*71 = 72
                uandf -> make_set(k + 1 + line*71);
                count += 1;
                if(k >= 1) {
                    //connects the previous set with the current object
                    if(nextLine[k - 1] == '+') 
                        uandf -> union_sets(k + line*71, k + 1 + line*71);
                }
                //connects the above set with the current object
                if(prevLine[k] == '+') 
                    uandf -> union_sets(k + 1 + (line - 1)*71, k + 1 + line*71);

            
            }

        }
        strcpy(prevLine, nextLine);

    }

    int reps = uandf -> final_sets();

    int *unsorted = new int[reps];

    printf("The total number of components is: %d\n", reps);
    Node **sets = uandf -> getSet();

    for(int j = 0; j < reps; j++) {
        int size = 0;
        for(int i = 0; i < 5041; i++) {
            if(sets[i] -> getParent() == j) size += 1;
        }
        printf("Component: %c has size %d\n", 65+j, size);
        unsorted[j] = size;
    }

    for(int j = 0; j < reps; j++) {
        printf("Component: %c\n", 65+j);
        for(int i = 0; i < 71; i++) {
            for(int y = 0; y < 71; y++) {
                if(sets[i*71 + y] -> getParent() == j) printf("+");
                else printf(" ");
            }
            printf("\n");
        }
    }

    int *sorted = new int[reps];
    for(int j = 0; j < reps; j++) {
        sorted[j] = j;
        int index = j;
        for(int y = j - 1; y >= 0; y--) {
            if(unsorted[sorted[index]] < unsorted[sorted[y]]) {
                int tmp = sorted[index];
                sorted[index] = sorted[y];
                sorted[y] = tmp;
                index = y;
            }
        }
    }

    for(int i = 0; i < reps; i++) 
        printf("%c has size %d\n", 65 + sorted[i], unsorted[sorted[i]]);


    printf("Printing components larger than 4!\n");
    for(int j = 0; j < reps; j++) {
        if(unsorted[j] > 4) {
            printf("Component: %c\n", 65+j);
            for(int i = 0; i < 71; i++) {
            for(int y = 0; y < 71; y++) {
                if(sets[i*71 + y] -> getParent() == j) printf("+");
                else printf(" ");
            }
            printf("\n");
        }
        
        }
    }
    return 0;
}