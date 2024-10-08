// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "mainwindow.h"
#include "Graph.h"
#include "Vertex.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    qInfo() << "Running";
    // Graph DC_graph(":/Data/vertex_test.txt");
    Graph DC_graph(":/Data/all_vertices.txt");

    // Vertex* v = DC_graph.getVertex(2);
    // v->print();

    MainWindow window(&DC_graph);
    window.show();



    // Graph g(":/Data/graph_dc_area_2022-03-11.txt");


    return app.exec();
}
