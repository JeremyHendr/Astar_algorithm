// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "Window.h"
#include "View.h"
#include "Graph.h"

#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
    ,scene(new QGraphicsScene(this)) {

    view = new View("Graph");
    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Graph"));
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
