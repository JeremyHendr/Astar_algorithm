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
    return (degrees * M_PI) / 180.0;
}

// QPoint* Vertex::polar_zero_reference;

Vertex::Vertex(uint32_t id, float longitude, float latitude){
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

void Vertex::print() const{
    qInfo() << "Vertex(id=" << id << ", x=" << coordinate->x() << ", y=" << coordinate->y() << ")";
}

const uint32_t Vertex::getID() const{
    return id;
}




