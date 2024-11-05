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
#include <unordered_map>
#include <QPen>

using namespace std;

enum class EdgeState {normal, visited, mainpath};

struct EdgeStyle {
    QPen pen;
};

class Edge : public QLine {
    public :
        Edge(uint32_t source_id, uint32_t dest_id, double length, string name, bool name_given=false);

        inline const uint32_t getSourceId() const {return source_id;};
        inline const uint32_t getDestinationId() const {return destination_id;};
        inline const double getLength()const {return length;};
        inline const string getName() const {return name;};
        inline const string getID() const {return id;};
        inline EdgeState getState(){return state;};
        inline QPen getPen(){return pen;};

        void inline setState(EdgeState s){
            state=s;
            const EdgeStyle& style = state_associated_style.at(s);
            pen=style.pen;
        }
        void print() const;


    private :
        string id;
        int source_id;
        int destination_id;
        double length;
        string name;

        //Members needed to draw the Edge
        static unordered_map<EdgeState, EdgeStyle> state_associated_style;
        EdgeState state = EdgeState::normal;
        QPen pen;

};


#endif
