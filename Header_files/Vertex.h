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
#include <vector>
//#include <functional> // Necessary for std::hash

using namespace std;


class Vertex {
    public :
        uint32_t id;

        // Default constructor
        //Vertex() : id(0), latitude(0.0), longitude(0.0), x(0), y(0), xy_given(false) {}

        // Parameterized constructor
        Vertex(uint32_t id, float latitude, float longitude, int x=0, int y=0, bool xy_given=false);

        // Retrieve characteristics of vertex
        uint32_t get_vertex_id(Vertex vertex) const;
        const float get_latitude(Vertex vertex);
        const float get_longitude(Vertex vertex);
        const int get_x(Vertex vertex);
        const int get_y(Vertex vertex);

        void print() const;
        void mercator();
        
        // Method to add connections to vertex
        void add_connection(Vertex vertex);

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
        
        
        pair<Vertex, vector<Edge>> vertex_connection; // Shows to which edges the vertex is connected
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