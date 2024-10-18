/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Vertex.cpp file
* Contains method definition for the Vertex class
*/

#include <QPoint>
#include <QApplication>

#include "Vertex.h"

using namespace std;

unordered_map<VertexState, QPen*> Vertex::state_associated_pen;
unordered_map<VertexState, QBrush*> Vertex::state_associated_brush;

double degreesToRadians(double degrees) {
    /* Convert degrees to radians
     *
     * @param double in degrees
     * @return double in radians
     */
    return (degrees * M_PI) / 180.0;
}

Vertex::Vertex(uint32_t id, float longitude, float latitude){
    /* Constructor for the vertex class with longitude and latitude
     * Converts those to x and y coordiantes using the mercator projection
     *
     * @param uint32_t id, float longitude, float latitude
     */

    //Set the coordinates of the first Vertex as 0 reference for mercators projection
    if (longitude_zero_reference == nullptr) {
        longitude_zero_reference = new double(longitude);
        latitude_zero_reference = new double(latitude);
        // qInfo() << "Setting the 0 polar reference to: " << longitude << " " << latitude;
    }

    this->id = id;
    double latRad = degreesToRadians(latitude);
    double lonRad = degreesToRadians(longitude);
    static double refLonRad = degreesToRadians(*longitude_zero_reference);
    static double refLatRad = degreesToRadians(*latitude_zero_reference);
    static const double R = 6378137.0; // Earth radius in meters

    // Mercator projection formulas
    // qInfo() << lonRad << " " << refLonRad << " " << *longitude_zero_reference << " " << longitude;
    int x = R * (lonRad - refLonRad);
    int y = R * log(tan(M_PI / 4 + latRad / 2) / tan(M_PI / 4 + refLatRad / 2));

    this->coordinate = new QPoint(x,y);

    //white circle filled red
    QPen* normal_pen = new QPen(Qt::white);
    QBrush* normal_brush = new QBrush(Qt::SolidLine);
    normal_pen->setWidth(5);
    normal_brush->setColor(Qt::red);
    state_associated_pen[VertexState::normal] = normal_pen;
    state_associated_brush[VertexState::normal] = normal_brush;
    ellipse_size = 5;

    //green circle filled green
    QPen* visited_pen = new QPen(Qt::green);
    QBrush* visited_brush = new QBrush(Qt::SolidLine);
    // visited_pen->setWidth(5);
    visited_brush->setColor(Qt::green);
    state_associated_pen[VertexState::visited] = visited_pen;
    state_associated_brush[VertexState::visited] = visited_brush;
    ellipse_size = 5;

    //Red circle filled red
    QPen* mainpath_pen = new QPen(Qt::red);
    QBrush* mainpath_brush = new QBrush(Qt::SolidLine);
    // mainpath_pen->setWidth(5);
    mainpath_brush->setColor(Qt::red);
    state_associated_pen[VertexState::mainpath] = mainpath_pen;
    state_associated_brush[VertexState::mainpath] = mainpath_brush;
    ellipse_size = 20;

    //blue circle filled green
    QPen* start_pen = new QPen(Qt::blue);
    QBrush* start_brush = new QBrush(Qt::SolidLine);
    start_pen->setWidth(15);
    start_brush->setColor(Qt::green);
    state_associated_pen[VertexState::start] = start_pen;
    state_associated_brush[VertexState::start] = start_brush;
    ellipse_size = 50;

    //blue circle filled red
    QPen* end_pen = new QPen(Qt::blue);
    QBrush* end_brush = new QBrush(Qt::SolidLine);
    end_pen->setWidth(15);
    end_brush->setColor(Qt::red);
    state_associated_pen[VertexState::end] = end_pen;
    state_associated_brush[VertexState::end] = end_brush;
    ellipse_size = 50;

    //blue circle filled blue
    QPen* deadend_pen = new QPen(Qt::blue);
    QBrush* deadend_brush = new QBrush(Qt::SolidLine);
    // deadend_pen->setWidth(15);
    deadend_brush->setColor(Qt::blue);
    state_associated_pen[VertexState::deadend] = deadend_pen;
    state_associated_brush[VertexState::deadend] = deadend_brush;
    ellipse_size = 20;

    this->pen = state_associated_pen.at(state);
    this->brush = state_associated_brush.at(state);
}


Vertex::Vertex(uint32_t id, int x, int y){
    /* Constructor for the vertex class with x and y
     *
     * @param uint32_t id, int x, int y
     */
    this->id = id;
    this->coordinate = new QPoint(x,y);
}


void Vertex::addNeighbor(pair<Vertex*, Edge*> pair){
    /* Add neighbor (vertex and edge) to vertex object
     *
     * @param pair<Vertex*, Edge*>
     */
    this->neighbors.push_back(pair);
}


void Vertex::showNeighbor(Vertex* v){
    /* Show neighbors and connections
     *
     * @param pointer to vertex object
     */
    v->print();
    qInfo() << "Neighbor vertices and edge connections: ";
    for (const auto& pair: v->neighbors){
        qInfo() << "Vertex: " << pair.first->getID() << " | Edge: " << pair.second->getID();
    }
}

vector<pair<Vertex*, Edge*>> Vertex::getNeighbors(){
    /* Retrieve the neighbors of the vertex
     *
     * @return vector<pair<Vertex*, Edge*>>
     */
    return this->neighbors;
}

void Vertex::print() const {
    /* Print description of vertex
     */
    qInfo() << "Vertex(id=" << id << ", x=" << coordinate->x() << ", y=" << coordinate->y() << ")";
}
