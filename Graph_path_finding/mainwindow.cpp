// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "chip.h"
#include "mainwindow.h"
#include "view.h"
#include "Graph.h"

#include <QHBoxLayout>
#include <QPainter>

MainWindow::MainWindow(Graph* graph, QWidget *parent): QWidget(parent), scene(new QGraphicsScene(this)) {
    populateScene(graph);

    View *view = new View("Top left view");
    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Chip Example"));
}

void MainWindow::populateScene(Graph* graph) {

    for(auto kv : graph->vertices_map) {
        int x = kv.second->getCoordinate()->x();
        int y = kv.second->getCoordinate()->y();
        // qInfo() << x << " " << y;
        QColor color(255,0,0);
        QGraphicsItem *item = new Chip(color, x, y);
        item->setPos(QPointF(x, y));
        scene->addItem(item);
    }
}
