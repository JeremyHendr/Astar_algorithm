#include "Window.h"

Window::Window( QObject *parent) : QGraphicsScene(parent) {
    //
}

void Window::displayGraph(Graph* graph) {
    //TODO if we wanna put a new map, remove the actual map and put the new

    addItem(graph);
    qInfo() << "Finished populating scene.";
}
