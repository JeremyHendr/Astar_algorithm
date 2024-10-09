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
#include <stdint.h>
#include <QPoint>
#include <QApplication>

#include "Edge.h"

using namespace std;

// Edge class constructor
Edge::Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given){
    /* Constructor for edge class
     *
     * @param uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given
     */

    if (name_given == true){
        this->name = name;
    }

    // Creation of unique edge id
    //QString("%1.%2").arg(source_id).arg(dest_id);;
    this->id = to_string(source_id) + "." + to_string(dest_id);



    this->source_id = source_id;
    this->dest_id = dest_id;
    this->length = length;
}

// Method to print edges
void Edge::print() const{
    /* Print edge description
    */
    cout << "Edge(Source id=" << source_id << ", dest id=" << dest_id << ", length=" << length << ")" << endl;
}

// Method to retrieve source id
const uint32_t Edge::get_source_id() const{
    /* Retrieve source id of edge
     *
     * @return uint32_t for source id of edge
     */
    return source_id;
}

// Method to retrieve destination id
const uint32_t Edge::get_destination_id() const{
    /* Retrieve destination id of edge
     *
     * @return uint32_t for destination id of edge
     */
    return dest_id;
}

// Method to retrieve length
const double Edge::get_length(Edge edge){
    /* Retrieve length of edge
     *
     * @param edge e
     * @return double for length of edge
     */
    return edge.length;
}

// Method to retrieve name
const string Edge::get_name(Edge edge){
    /* Retrieve name of edge
     *
     * @param edge e
     * @return Standard string for edge
     */
    return edge.name;
}

// Method to retrieve id
const string Edge::getID() const{
    /* Retrieve the unique edge id
     *
     * @param edge e
     * @return double for edge id
     */
    return id;
}


