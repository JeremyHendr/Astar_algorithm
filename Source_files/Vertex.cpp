#include <unordered_map>

#include "Vertex.h"

Vertex::Vertex(int latitude, int longitude, uint32_t id, int x=none, int y=none) {
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