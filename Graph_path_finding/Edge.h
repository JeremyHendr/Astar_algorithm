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

#include <iostream>



using namespace std;


class Edge {
public :
    Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given=false);

    static int get_source_id(Edge edge);
    static int get_destination_id(Edge edge);
    const double get_length(Edge edge);
    const string get_name(Edge name);
    const double getID() const;

    void print() const;

private :
    double id;
    int source_id;
    int dest_id;
    double length;
    string name;
};


#endif
