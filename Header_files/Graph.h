#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include "Vertex.h"
#include "Edge.h"
#include <string>

using std::string;

class Graph {
    public:
        Graph(string graph_data_file);

        void BFS();
        void Dijkstra();
        void Astar();
    
    private:
        std::unordered_map<std::int, Vertex > vertices_map;
        std::unordered_map<std::int, Edge > edge_map;
}


#endif

// this_is_my_int
// thisIsMyFunction
// ThisIsMyClass