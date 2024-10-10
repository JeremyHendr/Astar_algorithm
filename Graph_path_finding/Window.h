#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsScene>

#include "Graph.h"

class Window : public QGraphicsScene {
    Q_OBJECT
    public:
        Window(QObject  *parent = nullptr );
        void displayGraph(Graph* graph);

    private:

};

#endif // WINDOW_H
