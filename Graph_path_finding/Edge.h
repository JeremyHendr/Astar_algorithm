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

        const uint32_t getSourceId() const;
        const uint32_t getDestinationId() const;
        const double getLength()const;
        const string getName() const;
        const string getID() const;

        void print() const;

    private :
        string id;
        int source_id;
        int destination_id;
        double length;
        string name;
};


#endif
