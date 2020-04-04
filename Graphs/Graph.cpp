#include "Graph.hpp"

//Creates a graph object
//param n: Number of vertices in the graph
Graph::Graph(int n) : vertices(n) {
    //create the array of vectors that stores each vertices edges
    edges = new vector<Edge>[n];
    
}

//Put an edge into the graph
//param start: vertex id where the edge originates
//param dest: vertex id where the edge ends
//param weight: weight of the edge
void Graph::put_edge(int start, int dest, int weight) {
    //start or end is out of range
    if(start > vertices || dest > vertices) return;
    //create the edge
    Edge edge;
    edge.start_vertex = start;
    edge.end_vertex = dest;
    edge.weight = weight;
    //put the edge in both the arrays for start and dest
    //since this is an undirected graph
    edges[start - 1].push_back(edge);
    edges[dest - 1].push_back(edge);
    
}

//Returns the number of vertices
int Graph::num_vertices() {
    return vertices;
}

//Returns the incident edges on vertex
//param vertex: id of the vertex whose edges you want
vector<Edge> Graph::get_edges(int vertex) {
    return edges[vertex - 1];
}

//Returns the number of vertices in a graph
int Graph::size() {
    return vertices;
}

//Helper function for printing... (TO-DO: Override operator<< instead)
void Graph::print() {
    for(int i = 0; i < size(); i++) {
        cout << "Vertex: " << i + 1 << endl;
        vector<Edge> tmp_edges = get_edges(i + 1);
        for(size_t j = 0; j < tmp_edges.size(); j++) {
            Edge tmp = tmp_edges.at(j);
            int dest = tmp.start_vertex == i+1 ? tmp.end_vertex : tmp.start_vertex;
            cout << "\tDest: " << dest << " Weight: " << tmp.weight << endl;
        }
    }
}