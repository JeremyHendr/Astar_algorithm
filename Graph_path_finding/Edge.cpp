/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.cpp file
* Contains method definition for the Edge class
*/

// #include <iostream>
// #include <sstream>
#include <string>
#include <stdint.h>
#include <QPoint>
#include <QApplication>

#include "Edge.h"

using namespace std;

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
    this->destination_id = dest_id;
    this->length = length;
}

void Edge::print() const{
    /*
     * Print edge description
     */
    qInfo() << "Edge(Source id=" << source_id << ", dest id=" << destination_id << ", length=" << length << ")";
}


const uint32_t Edge::getSourceId() const{
    /* Retrieve source id of edge
     *
     * @return uint32_t for source id of edge
     */
    return source_id;
}


const uint32_t Edge::getDestinationId() const{
    /* Retrieve destination id of edge
     *
     * @return uint32_t for destination id of edge
     */
    return destination_id;
}


const double Edge::getLength() const{
    /* Retrieve length of edge
     *
     * @return double for length of edge
     */
    return length;
}


const string Edge::getName() const{
    /* Retrieve name of edge
     *
     * @return Standard string for edge
     */
    return name;
}


const string Edge::getID() const{
    /* Retrieve the unique edge id
     *
     * @return double for edge id
     */
    return id;
}


