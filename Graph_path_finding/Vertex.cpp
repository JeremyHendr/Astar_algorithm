/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Vertex.cpp file
* Contains method definition for the Vertex class
*/

#include <QPoint>
#include <iostream>

#include "Vertex.h"

using namespace std;

Vertex::Vertex(uint32_t id, float longitude, float latitude){
    this->id = id;
    int x=0;
    int y=0;

    //TODO perform mercator's projection to get plannar coordinates

    this->coordinate = new QPoint(x,y);
}

void Vertex::print() const{
    cout << "Vertex(id=" << id << ", x=" << coordinate->x() << ", y=" << coordinate->y() << ")" << endl;
}

const uint32_t Vertex::getID() const{
    return id;
}

