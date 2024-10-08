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
#include <string>
#include <cstdint>
#include <iostream>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"


using namespace std;

Graph::Graph(string graph_data_file) {

    QFile file(":/Data/graph_dc_area_2022-03-11.txt");
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

        if (fields[0] == "V") { //V,vertexid,longitude,latitude,x*,y*
            uint32_t ID = fields[1].toUInt();
            float latitude = fields[2].toFloat();
            float longitude = fields[2].toFloat();
            Vertex* v = new Vertex(ID, latitude, longitude);
            add_vertex(v);
        }
        else if (fields[0] == "E") {
            //Create a new Edge object
            //add to the edge map
            //add the destination vertex as neighbor of the origin vertex
        }
    }

    file.close();
}


// Method to add vertices (Format: V,vertexid,longitude,latitude,x*,y*)
void Graph::add_vertex(Vertex* v){
    //check is not already inside
    vertices_map.insert({v->getID(), v});
}

// Method to add edges (Format: E,source_vid,dest_vid,length,name,extra0,extra1)
void Graph::add_edge(Edge* e){
    //check is not already inside
    edges_map.insert({e->getID(), e});
}

// Method to print description of the graph
void Graph::print() const{
    cout << "Graph with " << vertices_map.size() << " vertices and " << edges_map.size() << " edges" << endl;
}


// vector<Vertex*> Graph::BFS(Vertex* origin, Vertex* destination, bool time){
//     // Method for the BFS algorithm
//     //TODO
// }
