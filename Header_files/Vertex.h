/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Vertex.h file 
* Contains header definition for the Vertex class
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <unordered_map>
#include <functional> // Necessary for std::hash

using namespace std;

class Vertex {
    public :
        uint32_t id;

        Vertex(uint32_t id, float latitude, float longitude, int x=0, int y=0, bool xy_given=false);

        // Retrieve characteristics of vertex
        uint32_t get_vertex_id(Vertex vertex);
        float get_latitude(Vertex vertex);
        float get_longitude(Vertex vertex);
        int get_x(Vertex vertex);
        int get_y(Vertex vertex);

        void print() const;
        void mercator();
        

        Vertex getClosestVertex();

        // Equality operator to compare two Vertex objects
        bool operator==(const Vertex& other) const{
            return id == other.id; // Compare by unique id
        }
    
    private :
        float latitude;
        float longitude;
        int x;
        int y;
        bool xy_given;
        
        
        unordered_map<Vertex, Edge > connected_vertices;
};

// Custom hash function for Vertex to work with unordered_map
namespace std{
    template<>
    struct hash<Vertex>{
        std::size_t operator()(const Vertex& v) const {
            return std::hash<uint32_t>()(v.id); // Hash based on vertex ID
        }
    };
}


#endif VERTEX_H