/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Edge.h file
* Contains header definition for the Edge class
*/

#ifndef EDGE_H
#define EDGE_H

#include <stdint.h>
#include <QPoint>
#include <QApplication>
#include <QBrush>
#include <QPen>
#include <QGraphicsLineItem>


using namespace std;


class Edge : public QGraphicsLineItem{
    public :
        Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given=false);

        const uint32_t getSourceId() const;
        const uint32_t getDestinationId() const;
        const double getLength()const;
        const string getName() const;
        const string getID() const;
        void setCoordinates(QPoint* source, QPoint* destination);
        void print() const;

    private :
        QPen* line_pen = new QPen();
        inline static QColor line_color = Qt::green;
        inline static const int line_width = 5;
        string id;
        int source_id;
        int destination_id;
        double length;
        string name;
        QPoint* source_coordinate;
        QPoint* destination_coordinate;
};


#endif
