/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Vertex.h file
* Contains header definition for the Vertex class
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>
#include <vector>

#include "Edge.h"

using namespace std;

class Vertex {
    public :
        Vertex(uint32_t id, float longitude, float latitude);
        Vertex(uint32_t id, int x, int y);

        inline const uint32_t getID() const {return id;};
        inline QPoint* getCoordinate() const {return coordinate;};
        inline static double* getLongitudeZeroReference() {return longitude_zero_reference;}
        inline static double* getLatitudeZeroReference() {return latitude_zero_reference;}

        // Manage the neighbors for each vertex object
        void print() const;
        void addNeighbor(pair<Vertex*, Edge*> p);
        void showNeighbor(Vertex* v);
        vector<pair<Vertex*, Edge*>> getNeighbors();

    private :
        inline static double* longitude_zero_reference = nullptr;
        inline static double* latitude_zero_reference = nullptr;
        uint32_t id;
        QPoint* coordinate;
        vector< pair<Vertex*, Edge*> > neighbors; // Pair of vertex that can be reached and with the edge with which it can be reached
};

#endif
