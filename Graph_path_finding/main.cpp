// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "Graph.h"
#include "Window.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    // Graph DC_graph(":/Data/vertex_test.txt");
    // Graph DC_graph(":/Data/all_vertices.txt");
    Graph DC_graph(":/Data/graph_dc_area_2022-03-11.txt");

    MainWindow window;
    window.show();
    window.setGraph(&DC_graph);

    return app.exec();
}
