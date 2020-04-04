#include <iostream>
#include <string>
#include <cstring>
#include "Graph.hpp"
#include "Heap.hpp"

using namespace std;

//Computes prims minimum spanning tree on Graph graph with root, source
//param graph: graph to find mst
//param source: starting vertex of mst
void prims_mst (Graph graph, int source) {
    //Keys[source] will be 0 and the rest INFINITY
    float keys[graph.size()] = {};
    //parent[i] stores the index of the vertex that leads to i
    int parent[graph.size()] = {};

    //initialize the keys
    for(int i = 0; i < graph.size(); i ++) {
        keys[i] = INFINITY;
    }
    //set the source key to be the minimum value
    keys[source] = 0;
    //Create the heap
    Heap heap(keys, graph.size());
    
    //Start prims algorithm
    int i = 0;
    while(!heap.is_empty()) {
        
        //peak the vertex id with the smallest key
        int vertex = heap.min_id();

        //print paths that have been established
        if(i != 0) {
            cout << "(" << parent[vertex - 1] << ", " << vertex << ") Weight: "<< heap.key(vertex) << endl; 
        }

        //delete the minimum key
        heap.delete_min();
        
        //get the indicident edges on vertex
        vector<Edge> adj = graph.get_edges(vertex);
        
        //Loop through each edge
        for(size_t j = 0; j < adj.size(); j++) {
            //extract the edge
            Edge edge = adj.at(j);

            //The adj_vertex is either start_vertex or end_vertex, depending on which is
            //equal to the current vertex. Since the graph is undirected
            int adj_vertex = edge.start_vertex == vertex ? edge.end_vertex : edge.start_vertex;

            //check that the adj_vertex has not already been computed
            //and that the key of that vertex is larger than the new weight found
            if(heap.in_heap(adj_vertex) && heap.key(adj_vertex) > edge.weight) {
                parent[adj_vertex - 1] = vertex ;
                heap.decrease_key(adj_vertex, edge.weight);
            }
        }
        i+=1;
    }
}

int main() {
    //Get the first line of the file describing number of vertices
    string line;
    getline(cin, line);
    
    //create the graph
    Graph g(stoi(line));
    
    //read the remaining lines to get the edges
    while(getline(cin, line)) {
        //each line has variable spacing between values
        //start_ind finds the position of the first space
        //The substring of length start_ind chars is the first value
        int start_ind = line.find(' ', 0);
        
        //since each line has variable spaces, end_ind is the position
        //of the first character which isn't a space.
        int end_ind = start_ind;
        while(line[end_ind] == ' ') end_ind += 1;

        //Starting from end_ind, find the first occurence of a space
        //the second value is the substring starting from end_ind
        //and spanning end_ind_last - end_ind
        int end_ind_last = line.find(' ', end_ind);

        //The last value is found the same way as the previous ones
        int w_ind = end_ind_last;
        while(line[w_ind] == ' ') w_ind += 1;

        //extract all the substrings
        string start = line.substr(0, start_ind),
        end = line.substr(end_ind, end_ind_last - end_ind),
        weight = line.substr(w_ind, line.find(' ', w_ind + 1 ) - w_ind);

        //insert the edge into the graph
        g.put_edge(stoi(start), stoi(end), stoi(weight));
    }
    
    //output the graph in Adjacency List format
    g.print();

    //Run prims minimum spanning tree algorith with root = 0
    prims_mst(g, 0);
    return 0;
}