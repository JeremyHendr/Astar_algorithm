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

        void addVertex(Vertex* v);
        void addEdge(Edge* e);
        Vertex* getVertex(uint32_t id);
        Edge* getEdge(string id);
        void print() const;

        unordered_map<uint32_t, Vertex*> vertices_map;
        unordered_map<string, Edge*> edges_map;

        // Path algorithms
        // vector<Vertex*> BFS(Vertex* origin, Vertex* destination, bool time=false);
        // void Dijkstra();
        // void Astar();




};


#endif

