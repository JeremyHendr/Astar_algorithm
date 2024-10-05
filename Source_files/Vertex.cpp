/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Vertex.cpp file 
* Contains method definition for the Vertex class
*/

#include <unordered_map>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

// Vertex class constructor
Vertex::Vertex(uint32_t id, float longitude, float latitude, int x=0, int y=0, bool xy_given=false){
    if (xy_given == true){
        this->x = x;
        this->y = y;
    }

    this->id = id;
    this->x = 0;
    this->y = 0;
    this->xy_given = xy_given;
}

// Method to add connection from this vertex to another one through an edge
void Vertex::add_connection(Vertex vertex){
    const auto& edges_map = Graph::get_edges_map(); // Retrieve the edges_map
    vertex_connection.first = vertex; // Add the vertex as the first element of the pair

    vector<Edge> edge_vec;
    for (const auto& pair: edges_map){
        if (Edge::get_source_id(*pair.second) == Vertex::get_vertex_id(vertex)){ // (*pair.second dereferences the pointer and gives the object)
            edge_vec.push_back(*pair.second);
        }
    }

    vertex_connection.second = edge_vec; // Add the full edge vector to the vertex/edge pair
}


// Print function for vertices
void Vertex::print() const{
    cout << "Vertex(id=" << id << ", lat=" << latitude << ", lon=" << longitude << ")" << endl; 
}

// Method to retrieve vertex id
uint32_t Vertex::get_vertex_id(Vertex vertex) const{
    return vertex.id;
}

// Method to retrieve latitude
const float Vertex::get_latitude(Vertex vertex){
    return vertex.latitude;
}

// Method to retrieve longitude
const float Vertex::get_longitude(Vertex vertex){
    return vertex.longitude;
}

// Method to retrieve x coordinate
const int Vertex::get_x(Vertex vertex){
    if (vertex.xy_given == true){
        return vertex.x;
    }
}

// Method to retrieve y coordinate
const int Vertex::get_y(Vertex vertex){
    if (vertex.xy_given == true){
        return vertex.y;
    }
}

// Mercator's projection (for Dijkstra Algorithm)
void Vertex::mercator(){

} 