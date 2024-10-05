/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file 
* Contains method definition for the Graph class
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <utility>
#include <unordered_map>


#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

/*
using std::string;
using std::vector;
using std::stoi;
using std::stof;
using std::stod;
using std::unordered_map;
*/

using namespace std;

Graph::Graph(string graph_data_file) {
    // Read file and store it in a map
    string file_name{graph_data_file};

    std::ifstream file(file_name, std::ios::in);
    // Check if file is open
    if (!file.is_open()){
        std::cerr << "Error: Could not open the map file !" << std::endl;
    }

    string line;
    // Read the every line of the file
    while (std::getline(file, line)){
        std::stringstream ss(line);
        string value;
        vector<string> row;

        // Split line by commas and save value in vector
        while (std::getline(ss, value, ',')){
            row.push_back(value);
        }

        if (row[0] == "V"){ // Vertex detected
            add_vertex(row);
        }

        else if (row[0] == "E"){ // Edge detected
            add_edge(row);
        }

        else if (row[0] == "#"){ // Comment has been detected -> skip
        }

    }

    file.close();


}


// Method to add vertices (Format: V,vertexid,longitude,latitude,x*,y*)
void Graph::add_vertex(vector<string> row){
    // Create vertex object with arguments: latitude (float) / longitude (float) / id (uint32_t) / x (int) / y (int)
    Vertex* v;
    if (row.size() == 6){ // We have values for x and y
        bool xy_given = true;
        v = new Vertex(stof(row[2]), stof(row[3]), static_cast<uint32_t>(stoi(row[1])), stoi(row[4]), stoi(row[5]), xy_given);
    }
    else { 
        v = new Vertex(stof(row[2]), stof(row[3]), static_cast<uint32_t>(stoi(row[1])));
    }

    // Add created object to unordered map (id, vertex object)
    vertices_map.insert({static_cast<uint32_t>(stoi(row[1])), v});

}

// Method to add edges (Format: E,source_vid,dest_vid,length,name,extra0,extra1)
void Graph::add_edge(vector<string> row){
    // Create edge object with arguments and store it: source id (int) / destination id (int) / length (double) / name (string)
    Edge* e;

    // Create a unique edge id: source_id.dest_id
    double unique_id = Edge::create_edge_id(stoi(row[1]), stoi(row[2]));

    if (row.size() == 5){
        bool name_given = true;
        e = new Edge(unique_id, stoi(row[1]), stoi(row[2]), stod(row[3]), row[4], name_given);
    }
    else{
        e = new Edge(unique_id, stoi(row[1]), stoi(row[2]), stod(row[3]), row[4]);
    }

    
    // Add created object to unordered map (id, edge object)
    edges_map.insert({unique_id, e});
}

// Method to print description of the graph
void Graph::print() const{
    cout << "Graph with " << vertices_map.size() << " vertices and " << edges_map.size() << " edges" << endl;
}

// Method to retrieve the edges_map
const std::unordered_map<double, Edge*>& Graph::get_edges_map(){
    return edges_map;
}

// Method for the BFS algorithm
void Graph::BFS(){ 

}