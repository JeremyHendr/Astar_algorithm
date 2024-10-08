/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.cpp file
* Contains method definition for the Edge class
*/

#include <iostream>
#include <sstream>
#include <string>

#include "Edge.h"

using namespace std;

// Edge class constructor
Edge::Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given){
    if (name_given == true){
        this->name = name;
    }
    std::ostringstream oss;
    oss << source_id << "." << dest_id;
    this->id = std::stod(oss.str());
    this->source_id = source_id;
    this->dest_id = dest_id;
    this->length = length;


}

// Method to print edges
void Edge::print() const{
    cout << "Edge(Source id=" << source_id << ", dest id=" << dest_id << ", length=" << length << ")" << endl;
}

// Method to retrieve source id
int Edge::get_source_id(Edge edge){
    return edge.source_id;
}

// Method to retrieve destination id
int Edge::get_destination_id(Edge edge){
    return edge.dest_id;
}

// Method to retrieve length
const double Edge::get_length(Edge edge){
    return edge.length;
}

// Method to retrieve name
const string Edge::get_name(Edge edge){
    return edge.name;
}
const double Edge::getID() const{
    return id;
}
// Method to create a unique edge id
// double Edge::create_edge_id(int source_id, int dest_id){
//     std::ostringstream oss;
//     oss << source_id << "." << dest_id;
//     return std::stod(oss.str());
// }
