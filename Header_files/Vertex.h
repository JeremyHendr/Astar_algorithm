#ifndef VERTEX_H
#define VERTEX_H

#include <unordered_map>
#include <iostream>
class Vertex {
    public :
        Vertex(int latitude, int longitude, uint32_t id, int x=0, int y=0);

        int getX();
        int getY();
        uint32_t getID();

        Vertex getClosestVertex();
    
    private :
        int x;
        int y;
        uint32_t id;
       std::unordered_map<Vertex, Edge > connected_vertices;
};


#endif VERTEX_H