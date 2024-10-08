/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file
* Contains method definition for the Graph class
*/


#include <unordered_map>
#include <QFile>
#include <QApplication>
#include <cstdint>
#include <iostream>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"


using namespace std;

Graph::Graph(QString graph_data_file) {

    QFile file(graph_data_file);
    if(!file.open(QIODevice::ReadOnly)) {
        qInfo() << "Could not open file";
        qInfo() << file.errorString();
    }

    //TODO check if all the vertex are read before the edge
    //Or first store all the vertex and edge and then loop the edge map
    //and add the destination vertex as neighbor of the origin vertex

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        // qInfo() << fields;

        if (fields[0] == "V") { //V,vertexid,longitude,latitude,x*,y*
            uint32_t ID = fields[1].toUInt();
            float longitude = fields[2].toFloat();
            float latitude = fields[3].toFloat();
            Vertex* v = new Vertex(ID, longitude, latitude);
            addVertex(v);
        }

        else if (fields[0] == "E") {
            //Create a new Edge object
            //add to the edge map
            //add the destination vertex as neighbor of the origin vertex
        }
    }

    file.close();
    print();
}


// Method to add vertices (Format: V,vertexid,longitude,latitude,x*,y*)
void Graph::addVertex(Vertex* v){
    //check is not already inside
    vertices_map.insert({v->getID(), v});
}

// Method to add edges (Format: E,source_vid,dest_vid,length,name,extra0,extra1)
void Graph::addEdge(Edge* e){
    //check is not already inside
    edges_map.insert({e->getID(), e});
}

// Method to print description of the graph
void Graph::print() const{
    qInfo() << "Graph with " << vertices_map.size() << " vertices and " << edges_map.size() << " edges";
}

Vertex* Graph::getVertex(uint32_t id) {
    // std::vector<uint32_t> keys;
    // keys.reserve(vertices_map.size());

    // for(auto kv : vertices_map) {
    //     keys.push_back(kv.first);
    // }
    // qInfo() << keys;

    if (vertices_map.find(id) == vertices_map.end()) {
        qInfo() << "No Vertex with id" << id;
        return nullptr;
    }
    return vertices_map.at(id);
}

Edge* Graph::getEdge(double id) {
    auto it = edges_map.find(id);
    if (it != edges_map.end()) {
        return it->second;
    } else {
        return nullptr; // Return nullptr if the edge is not found
    }
}

// vector<Vertex*> Graph::BFS(Vertex* origin, Vertex* destination, bool time){
//     // Method for the BFS algorithm
//     //TODO
// }
