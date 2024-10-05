/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.cpp file 
* Contains method definition for the Edge class
*/

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>

#include "Edge.h"
#include "Vertex.h"

using namespace std;

// Edge class constructor 
Edge::Edge(int source_id, int dest_id, double length, string name, bool name_given=false){
    if (name_given == true){
        this->name = name;
    }

    this->source_id = source_id;
    this->dest_id = dest_id;
    this->length = length;
    

}

// Method to print edges
void Edge::print() const{
    cout << "Edge(Source id=" << source_id << ", dest id=" << dest_id << ", length=" << length << ")" << endl; 
}

// Method to retrieve source id
int Edge::get_source(Edge edge){
    return edge.source_id;
}

// Method to retrieve destination id
int Edge::get_destination(Edge edge){
    return edge.dest_id;
}

// Method to retrieve length
double Edge::get_length(Edge edge){
    return edge.length;
}

// Method to retrieve name
string Edge::get_name(Edge edge){
    return edge.name;
}

// Method to create a unique edge id
double Edge::create_edge_id(int source_id, int dest_id){
    std::ostringstream oss;
    oss << source_id << "." << dest_id;
    return std::stod(oss.str());
}