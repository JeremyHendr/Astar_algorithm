/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.h file 
* Contains header definition for the Edge class
*/


#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

using namespace std;


class Edge {
    public : 
        Edge(int source_id, int dest_id, double length, string name, bool name_given=false);

        void print() const;
        int get_source(Edge edge);
        int get_destination(Edge edge);
        double get_length(Edge edge);
        string get_name(Edge name);

        double get_edge_id(Edge edge);
        static double create_edge_id(int source_id, int dest_id);


    private :
        int source_id;
        int dest_id;
        double length;
        string name;

};


#endif EDGE_H