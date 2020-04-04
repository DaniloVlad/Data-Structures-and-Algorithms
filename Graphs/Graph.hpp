#ifndef _Graph
#define _Graph
#include <iostream>
#include <vector>

using namespace std;

//Struct used to store information about edges
typedef struct edge {
    int start_vertex;
    int end_vertex;
    int weight;
} Edge;


class Graph {
    public:
        Graph(int n);
        void put_edge(int start, int end, int weight);
        vector<Edge> get_edges(int vertex_id);
        int num_vertices();
        int size();
        void print();

    private:
        //Number of vertices
        int vertices;
        //Edges for each vertex
        vector<Edge>* edges;
};

#endif
