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
#include <QBrush>
#include <QPen>
#include <vector>
#include <QGraphicsEllipseItem>

#include "Edge.h"

using namespace std;

class Vertex : public QGraphicsEllipseItem {
    public :
        Vertex(uint32_t id, float longitude, float latitude);
        Vertex(uint32_t id, int x, int y);

        const uint32_t getID() const;
        inline const QPoint* getCoordinate() const{return coordinate;};
        void print() const;
        // static double* getLongitudeZeroReference() {return longitude_zero_reference;}
        // static double* getLatitudeZeroReference() {return latitude_zero_reference;}

        // Manage the neighbors for each vertex object
        void addNeighbor(pair<Vertex*, Edge*> p);
        void showNeighbor(Vertex* v);
        QPoint* getCoordinate();

    private :
        //inline static
        QBrush* node_brush = new QBrush(Qt::SolidPattern);
        QPen* node_pen = new QPen();
        inline static QColor node_color = Qt::white;
        inline static const int node_size = 20;
        inline static double* longitude_zero_reference = nullptr;
        inline static double* latitude_zero_reference = nullptr;
        uint32_t id;
        QPoint* coordinate;
        vector< pair<Vertex*, Edge*> > neighbors; // Pair of vertex that can be reached and with the edge with which it can be reached
};

#endif
