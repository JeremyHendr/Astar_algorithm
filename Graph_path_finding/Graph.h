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

// #include <iostream>
#include <unordered_map>
#include <QString>

#include "Vertex.h"
#include "Edge.h"

using namespace std;

class Graph {
    public:
        Graph(QString graph_data_file);

        void print() const;

        // Path algorithms
        // vector<Vertex*> BFS(Vertex* origin, Vertex* destination, bool time=false);
        // void Dijkstra();
        // void Astar();

        // Make the "edges_map" accessible
        // static const std::unordered_map<double, Edge*>& get_edges_map();

        // unordered_multimap<Vertex, Edge> connected_graph;



    private:
        void add_vertex(Vertex* v);
        void add_edge(Edge* e);

        unordered_map<uint32_t, Vertex*> vertices_map;
        unordered_map<double, Edge*>* edges_map;


};


#endif

