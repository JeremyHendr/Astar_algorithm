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
#include <QWidget>
#include <QGraphicsScene>

#include "Vertex.h"
#include "Edge.h"


using namespace std;

class Graph: public QGraphicsScene {
    Q_OBJECT
    public:
        Graph(QString graph_data_file,  QObject  *parent = nullptr );

        // Add element to corresponding map
        void addVertex(Vertex* v);
        void addEdge(Edge* e);

        // Retrieve element by id
        Vertex* getVertex(uint32_t id);
        Edge* getEdge(string id);

        // Print graph description
        void print() const;

        // BFS
        void BFS(uint32_t start, uint32_t end);
        vector<Vertex*> getBFSPath();
        void printBFSPath(int total_visited_vertex);

    private:
        // QGraphicsScene *scene;
        unordered_map<uint32_t, Vertex*> vertices_map;
        unordered_map<string, Edge*> edges_map;

        // Elements for the BFS
        vector<Vertex*> BFS_path;

        void populateScene();
        // Path algorithms
        // vector<Vertex*> BFS(Vertex* origin, Vertex* destination, bool time=false);
        // void Dijkstra();
        // void Astar();

};


#endif

