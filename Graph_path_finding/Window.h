// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Graph.h"
#include "View.h"


QT_BEGIN_NAMESPACE
class QGraphicsScene;
// class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        void setGraph(Graph* graph);

    private:
        View *view;
        QGraphicsScene *scene;
        Graph* displayed_graph = nullptr;

        void setupMatrix();
};

#endif // MAINWINDOW_H



