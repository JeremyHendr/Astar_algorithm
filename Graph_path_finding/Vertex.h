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
        Vertex(uint32_t id, float latitude, float longitude);
        Vertex(uint32_t id, int x, int y);

        const uint32_t getID() const;
        void print() const;
        void mercator();

    private :
        uint32_t id;
        QPoint* coordinate;
        vector< pair<Vertex*, Edge*> > neighbors;
};

#endif
