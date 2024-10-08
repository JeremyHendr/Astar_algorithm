/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file
* Contains method definition for the Graph class
*/


#include <string>
#include <vector>
#include <unordered_map>
#include <QFile>
#include <QApplication>

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
        // qInfo() << fields;
        if (fields[0] == "V") {
            //Create a new Vertex object

            //TODO assign lattitude and longitude
            uint32_t ID;
            float lattitude;
            float longitude;
            Vertex* v = new Vertex(ID, lattitude, longitude);
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
void Graph::add_edge(vector<string> row){
    // // Create edge object with arguments and store it: source id (int) / destination id (int) / length (double) / name (string)
    // Edge* e;

    // // Create a unique edge id: source_id.dest_id
    // double unique_id = Edge::create_edge_id(stoi(row[1]), stoi(row[2]));

    // if (row.size() == 5){
    //     bool name_given = true;
    //     e = new Edge(unique_id, stoi(row[1]), stoi(row[2]), stod(row[3]), row[4], name_given);
    // }
    // else{
    //     e = new Edge(unique_id, stoi(row[1]), stoi(row[2]), stod(row[3]), row[4]);
    // }


    // // Add created object to unordered map (id, edge object)
    // edges_map.insert({unique_id, e});
}

// Method to print description of the graph
void Graph::print() const{
    // cout << "Graph with " << vertices_map.size() << " vertices and " << edges_map.size() << " edges" << endl;
}

// Method to retrieve the edges_map
// const std::unordered_map<double, Edge*>& Graph::get_edges_map(){
//     return edges_map;
// }

// Method for the BFS algorithm
void Graph::BFS(){

}
