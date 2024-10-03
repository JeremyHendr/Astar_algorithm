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

Vertex::Vertex(float longitude, float latitude, uint32_t id, int x=0, int y=0) {
    if (x!=none && y!=none){
        this.x = x;
        this.y = y;
    }

    //TODO write the mercator's projection

    this.id = id
    this.x = 0;
    this.y = 0;
    connected_vertices = new std::unordered_map<Vertex, Edge>();
    
}