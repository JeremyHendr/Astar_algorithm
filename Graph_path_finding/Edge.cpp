/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.cpp file
* Contains method definition for the Edge class
*/

#include <QPoint>

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


void Edge::setCoordinates(QPoint* source, QPoint* destination) {
    /*Set the origin and destination coordinate
     *
     *@param QPoint* source, QPoint* destination
     */
    source_coordinate = source;
    destination_coordinate = destination;
}


void Edge::print() const{
    /*
     * Print edge description
     */
    qInfo() << "Edge(Source id=" << source_id << ", dest id=" << destination_id << ", length=" << length << ")";
}




