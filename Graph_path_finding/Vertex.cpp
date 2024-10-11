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

// Function to convert degrees to radians
double degreesToRadians(double degrees) {
    /* Convert degrees to radians
     *
     * @param double in degrees
     * @return double in radians
     */
    return (degrees * M_PI) / 180.0;
}

// QPoint* Vertex::polar_zero_reference;

// Constructor for the vertex class
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
    // print();
}

// Constructor for the vertex class with x and y
Vertex::Vertex(uint32_t id, int x, int y){
    /* Constructor for the vertex class with x and y
     *
     * @param uint32_t id, int x, int y
     */

    this->id = id;
    this->coordinate = new QPoint(x,y);
    // print();
}


// Method to print a vertex description
void Vertex::print() const{
    /* Print description of vertex
     */
    qInfo() << "Vertex(id=" << id << ", x=" << coordinate->x() << ", y=" << coordinate->y() << ")";
}

// Method to retrieve id of vertex
const uint32_t Vertex::getID() const{
    /* Retrieve vertex id
     *
     * @return const uint32_t for vertex id
     */
    return id;
}

// Method to add neighbor to vertex object
void Vertex::addNeighbor(pair<Vertex*, Edge*> pair){
    /* Add neighbor (vertex and edge) to vertex object
     *
     * @param pair<Vertex*, Edge*>
     */
    this->neighbors.push_back(pair);
}

// Method to display the neighbors of a vertex
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
