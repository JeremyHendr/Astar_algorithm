/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.cpp file
* Contains method definition for the Edge class
*/

#include <QPoint>
#include <math.h>

#include "Edge.h"

using namespace std;


unordered_map<EdgeState, EdgeStyle> Edge::state_associated_style;


Edge::Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given){
    /* Constructor for edge class
     *
     * @param uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given
     */

    if (name_given){
        this->name = name;
    }

    // Creation of unique edge id
    this->id = to_string(source_id) + "." + to_string(dest_id);
    this->source_id = source_id;
    this->destination_id = dest_id;
    this->length = length;

    // Initialize only once
    static bool initialized = false;
    if (!initialized) {
        state_associated_style[EdgeState::normal] = {
            QPen(Qt::white, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
        };
        state_associated_style[EdgeState::visited] = {
            QPen(Qt::green, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
        };
        state_associated_style[EdgeState::mainpath] = {
            QPen(Qt::red, 50, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
        };


    }
    const EdgeStyle& style = state_associated_style[state];
    this->pen = style.pen;
}



void Edge::print() const{
    /*
     * Print edge description
     */
    qInfo() << "Edge(Source id=" << source_id << ", dest id=" << destination_id << ", length=" << length << ")";
}




