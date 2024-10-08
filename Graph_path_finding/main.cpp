// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include <QApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "mainwindow.h"
#include "Graph.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;
    window.show();

    qInfo() << "Running";

    // Graph g(":/Data/graph_dc_area_2022-03-11.txt");
    Graph g(":/Data/vertex_test.txt");

    return app.exec();
}
