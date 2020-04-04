#ifndef NODE_H
#define NODE_H

//An object used to store member information
class Node {
    public:
        Node(int i);
        int getParent();
        int getMember();
        int getRank();
        void setParent(int parent);
        void setRank(int rank);
        int getSize();
        void setSize(int n);
    private:
        int parent;
        int member;
        int rank;
        int size;
};


#endif
