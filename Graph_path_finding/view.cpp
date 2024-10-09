#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>

#include "view.h"


View::View(QGraphicsScene* scene, QWidget *parent) : QGraphicsView(parent) {
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHints( QPainter::Antialiasing );
    setWindowTitle(tr("Chip Example"));
    setScene(scene);
}

void View::wheelEvent(QWheelEvent *event) {
    if(event->angleDelta().y() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);
}

void View::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left)
        rotate(1);
    else if(event->key() == Qt::Key_Right)
        rotate(-1);
}

