// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "Window.h"
#include "View.h"
#include "Graph.h"

#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
    ,scene(new QGraphicsScene(this)) {

    view = new View("Top left view");
    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Chip Example"));
    setWindowState(Qt::WindowActive | Qt::WindowMaximized);

}

void MainWindow::setGraph(Graph* graph) {
    if (displayed_graph != nullptr) {
        scene->removeItem(displayed_graph);
    }
    displayed_graph = graph;
    view->setGraph(graph);
    scene->addItem(graph);
    qInfo() << "Displaying new graph:"<<displayed_graph->getName();

}




// #include "Window.h"

// Window::Window(QObject *parent) : QGraphicsScene(parent) {
//     //
// }

// void Window::displayGraph(Graph* graph) {
//     //TODO if we wanna put a new map, remove the actual map and put the new

//     addItem(graph);
//     qInfo() << "Finished populating scene.";
// }
