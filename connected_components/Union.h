#ifndef UNION_H
#define UNION_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Node.h"

class Union {
    public:
        Union(int n);
        void make_set(int i);
        void union_sets(int i, int j);
        int find_set(int i);
        int final_sets();
        Node **getSet();
        int getSize();
    private:
        Node **sets;
        bool finalized;
        int total_sets;
        void Link(int x, int y);
};


#endif
