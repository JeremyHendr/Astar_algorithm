// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "Graph.h"
#include "view.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    // Graph DC_graph(":/Data/vertex_test.txt");
    Graph DC_graph(":/Data/all_vertices.txt");
    // Graph g(":/Data/graph_dc_area_2022-03-11.txt");

    // QGraphicsScene scene;
    // scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    // QGraphicsItem *item = new QGraphicsEllipseItem( -50.0, -50.0, 100.0, 100.0, Q_NULLPTR );
    // scene.addItem(item);

    // QGraphicsView view( &scene );
    // view.setRenderHints( QPainter::Antialiasing );
    // view.show();

    View v(&DC_graph);
    v.show();


    return app.exec();
}
