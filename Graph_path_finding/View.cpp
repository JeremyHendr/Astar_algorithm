#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QKeyEvent>

#include "View.h"


View::View(QGraphicsScene* scene, QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setInteractive(true);

    setWindowTitle(tr("Graph"));
    setScene(scene);
}

void View::wheelEvent(QWheelEvent *event) {
    if(event->angleDelta().y() > 0)
        scale(1.10, 1.10);
    else
        scale(0.9, 0.9);
}

void View::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left)
        rotate(3);
    else if(event->key() == Qt::Key_Right)
        rotate(-3);
}

