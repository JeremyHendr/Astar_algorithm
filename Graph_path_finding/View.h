#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>

class View : public QGraphicsView {
    Q_OBJECT
    public:
        View(QGraphicsScene* scene, QWidget *parent = nullptr);

    protected Q_SLOTS:
        void wheelEvent(QWheelEvent *event);
        void keyPressEvent(QKeyEvent *event);
};

#endif // VIEW_H
