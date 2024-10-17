// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QIntValidator>
#include <QComboBox>

#include "Graph.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView {
    Q_OBJECT
    public:
        GraphicsView(View *v) : QGraphicsView(), view(v) { }

    protected Q_SLOTS:
        void wheelEvent(QWheelEvent *event);
        void keyPressEvent(QKeyEvent *event);

    private:
        View *view;
};

class View : public QFrame {
    Q_OBJECT
    public:
        explicit View(const QString &name, QWidget *parent = nullptr);
        QGraphicsView *view() const;
        inline void setGraph(Graph* graph) {displayed_graph=graph;};


    private slots:
        void calculate_path();
        void reset_graph();


    private:
        Graph* displayed_graph;
        GraphicsView *graphicsView;
        QToolButton *reset_graph_button;
        QToolButton *calculate_path_button;
        QLineEdit *origin_input;
        QLineEdit *destination_input;
        QValidator *input_range;
        QComboBox *algorithm_selection;


        QLabel *label;
        QLabel *label2;
        QToolButton *selectModeButton;
        QToolButton *dragModeButton;
        QToolButton *antialiasButton;
        QToolButton *printButton;
        QToolButton *resetButton;
        QSlider *zoomSlider;
        QSlider *rotateSlider;
};

#endif // VIEW_H






// #ifndef VIEW_H
// #define VIEW_H

// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QGraphicsPixmapItem>
// #include <QWheelEvent>
// #include <QKeyEvent>
// #include <QToolButton>

// class View : public QGraphicsView {
//     Q_OBJECT
//     public:
//         View(QGraphicsScene* scene, QWidget *parent = nullptr);

//     protected Q_SLOTS:
//         void wheelEvent(QWheelEvent *event);
//         void keyPressEvent(QKeyEvent *event);

//     private:
//         QToolButton *resetButton;
//         QToolButton *pushButton;

//     private slots:
//         void resetView();
//         void setResetButtonEnabled();
//         void setupMatrix();
// };

// #endif // VIEW_H
