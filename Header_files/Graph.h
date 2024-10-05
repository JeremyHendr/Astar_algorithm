/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.h file 
* Contains header the Graph class
*/


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <string>

#include "Vertex.h"
#include "Edge.h"

using namespace std;

class Graph {
    public:
        Graph(string graph_data_file);

        void print() const;

        // Create the connections between a vertex and its edges
        void connect_graph(unordered_map<uint32_t, Vertex*> vertices_map);

        // Path algorithms
        void BFS();
        void Dijkstra();
        void Astar();

        // Make the "edges_map" accessible
        static const std::unordered_map<double, Edge*>& get_edges_map(); 
        
        unordered_multimap<Vertex, Edge> connected_graph;
        
        
    
    private:
        void add_vertex(vector<string> vec);
        void add_edge(vector<string> vec);

        static unordered_map<uint32_t, Vertex*> vertices_map;
        static unordered_map<double, Edge*> edges_map;

        
};


#endif

// this_is_my_int
// thisIsMyFunction
// ThisIsMyClass