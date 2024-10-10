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

using namespace std;


class Edge {
    public :
        Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given=false);

        inline const uint32_t getSourceId() const {return source_id;};
        inline const uint32_t getDestinationId() const {return destination_id;};
        inline const double getLength()const {return length;};
        inline const string getName() const {return name;};
        inline const string getID() const {return id;};
        inline QPoint* getSourceCoordinate() const {return source_coordinate;};
        inline QPoint* getDestinationCoordinate() const {return destination_coordinate;};

        void setCoordinates(QPoint* source, QPoint* destination);
        void print() const;


    private :
        string id;
        int source_id;
        int destination_id;
        double length;
        string name;
        QPoint* source_coordinate;
        QPoint* destination_coordinate;
};


#endif
