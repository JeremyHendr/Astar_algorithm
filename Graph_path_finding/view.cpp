#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>

#include "view.h"


View::View(QGraphicsScene* scene, QWidget *parent) : QGraphicsView(parent) {
    // setDragMode(QGraphicsView::ScrollHandDrag); //RubberBandDrag ScrollHandDrag
    // setRenderHints( QPainter::Antialiasing );
    // setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    // setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, false);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    setWindowTitle(tr("Chip Example"));
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

