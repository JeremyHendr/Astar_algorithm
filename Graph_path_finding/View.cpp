// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "view.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#include <QtWidgets>
#include <QtMath>

// void GraphicsView::wheelEvent(QWheelEvent *e) {
//     if (e->modifiers() & Qt::ControlModifier) {
//         if (e->angleDelta().y() > 0)
//             view->zoomInBy(6);
//         else
//             view->zoomOutBy(6);
//         e->accept();
//     } else {
//         QGraphicsView::wheelEvent(e);
//     }
// }

void GraphicsView::wheelEvent(QWheelEvent *event) {
    if(event->angleDelta().y() > 0)
        scale(1.10, 1.10);
    else
        scale(0.9, 0.9);
}
void GraphicsView::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left)
        rotate(3);
    else if(event->key() == Qt::Key_Right)
        rotate(-3);
}


View::View(const QString &name, QWidget *parent) : QFrame(parent) {
    setFrameStyle(Panel | Plain);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    // graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    // QSize iconSize(size, size);

    // QToolButton *zoomInIcon = new QToolButton;
    // zoomInIcon->setAutoRepeat(true);
    // zoomInIcon->setAutoRepeatInterval(33);
    // zoomInIcon->setAutoRepeatDelay(0);
    // zoomInIcon->setIcon(QPixmap(":/zoomin.png"));
    // zoomInIcon->setIconSize(iconSize);
    // QToolButton *zoomOutIcon = new QToolButton;
    // zoomOutIcon->setAutoRepeat(true);
    // zoomOutIcon->setAutoRepeatInterval(33);
    // zoomOutIcon->setAutoRepeatDelay(0);
    // zoomOutIcon->setIcon(QPixmap(":/zoomout.png"));
    // zoomOutIcon->setIconSize(iconSize);
    // zoomSlider = new QSlider;
    // zoomSlider->setMinimum(0);
    // zoomSlider->setMaximum(1000);
    // zoomSlider->setValue(250);
    // zoomSlider->setTickPosition(QSlider::TicksRight);

    // // Zoom slider layout
    // QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    // zoomSliderLayout->addWidget(zoomInIcon);
    // zoomSliderLayout->addWidget(zoomSlider);
    // zoomSliderLayout->addWidget(zoomOutIcon);

    // QToolButton *rotateLeftIcon = new QToolButton;
    // rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    // rotateLeftIcon->setIconSize(iconSize);
    // QToolButton *rotateRightIcon = new QToolButton;
    // rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    // rotateRightIcon->setIconSize(iconSize);
    // rotateSlider = new QSlider;
    // rotateSlider->setOrientation(Qt::Horizontal);
    // rotateSlider->setMinimum(-360);
    // rotateSlider->setMaximum(360);
    // rotateSlider->setValue(0);
    // rotateSlider->setTickPosition(QSlider::TicksBelow);

    // // Rotate slider layout
    // QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    // rotateSliderLayout->addWidget(rotateLeftIcon);
    // rotateSliderLayout->addWidget(rotateSlider);
    // rotateSliderLayout->addWidget(rotateRightIcon);

    // resetButton = new QToolButton;
    // resetButton->setText(tr("0"));
    // resetButton->setEnabled(false);

    // // Label layout
    // QHBoxLayout *labelLayout = new QHBoxLayout;
    // label = new QLabel(name);
    // label2 = new QLabel(tr("Pointer Mode"));
    // selectModeButton = new QToolButton;
    // selectModeButton->setText(tr("Select"));
    // selectModeButton->setCheckable(true);
    // selectModeButton->setChecked(true);
    // dragModeButton = new QToolButton;
    // dragModeButton->setText(tr("Drag"));
    // dragModeButton->setCheckable(true);
    // dragModeButton->setChecked(false);
    // antialiasButton = new QToolButton;
    // antialiasButton->setText(tr("Antialiasing"));
    // antialiasButton->setCheckable(true);
    // antialiasButton->setChecked(false);
    // printButton = new QToolButton;
    // printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

    // QButtonGroup *pointerModeGroup = new QButtonGroup(this);
    // pointerModeGroup->setExclusive(true);
    // pointerModeGroup->addButton(selectModeButton);
    // pointerModeGroup->addButton(dragModeButton);

    // labelLayout->addWidget(label);
    // labelLayout->addStretch();
    // labelLayout->addWidget(label2);
    // labelLayout->addWidget(selectModeButton);
    // labelLayout->addWidget(dragModeButton);
    // labelLayout->addStretch();
    // labelLayout->addWidget(antialiasButton);
    // labelLayout->addWidget(printButton);


    //TODO add those objects to header
    QHBoxLayout *vertex_selection = new QHBoxLayout;
    reset_graph_button = new QToolButton;
    reset_graph_button->setText(tr("Reset graph"));
    reset_graph_button->setCheckable(true);
    reset_graph_button->setChecked(false);
    vertex_selection->addWidget(reset_graph_button);

    calculate_path_button = new QToolButton;
    calculate_path_button->setText(tr("Calculate"));
    calculate_path_button->setCheckable(true);
    calculate_path_button->setChecked(false);
    vertex_selection->addWidget(calculate_path_button);


    input_range = new QIntValidator(0,100000);
    origin_input = new QLineEdit;
    origin_input->setPlaceholderText("Origin");
    origin_input->setMaxLength(6);
    origin_input->setValidator(input_range);
    vertex_selection->addWidget(origin_input);

    destination_input = new QLineEdit;
    destination_input->setPlaceholderText("Destination");
    destination_input->setMaxLength(6);
    destination_input->setValidator(input_range);
    vertex_selection->addWidget(destination_input);

    algorithm_selection = new QComboBox;
    algorithm_selection->addItem(tr("BFS"));
    algorithm_selection->addItem(tr("Dijkstra"));
    algorithm_selection->addItem(tr("Astar"));
    vertex_selection->addWidget(algorithm_selection);



    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(vertex_selection, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    // // topLayout->addLayout(zoomSliderLayout, 1, 1);
    // // topLayout->addLayout(rotateSliderLayout, 2, 0);
    // topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(reset_graph_button, &QAbstractButton::clicked, this, &View::reset_graph);
    connect(calculate_path_button, &QAbstractButton::clicked, this, &View::calculate_path);
    // connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    // connect(rotateSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    // connect(graphicsView->verticalScrollBar(), &QAbstractSlider::valueChanged,
    //         this, &View::setResetButtonEnabled);
    // connect(graphicsView->horizontalScrollBar(), &QAbstractSlider::valueChanged,
    //         this, &View::setResetButtonEnabled);
    // connect(selectModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    // connect(dragModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    // connect(antialiasButton, &QAbstractButton::toggled, this, &View::toggleAntialiasing);
    // connect(rotateLeftIcon, &QAbstractButton::clicked, this, &View::rotateLeft);
    // connect(rotateRightIcon, &QAbstractButton::clicked, this, &View::rotateRight);
    // connect(zoomInIcon, &QAbstractButton::clicked, this, &View::zoomIn);
    // connect(zoomOutIcon, &QAbstractButton::clicked, this, &View::zoomOut);
    // connect(printButton, &QAbstractButton::clicked, this, &View::print);

    // setupMatrix();
}


void View::calculate_path() {
    if (origin_input->hasAcceptableInput() && destination_input->hasAcceptableInput()) {
        qInfo()<<"acceptable input";
    }
    else {
        qInfo()<<"not acceptable input";
        calculate_path_button->setChecked(false);
        return;
    }
    switch(algorithm_selection->currentIndex()) {
        case 0: //call BFS algotithm
            qInfo() << "Algorithm: BFS, source:"<<origin_input->text()<<", destination:"<<destination_input->text();



            break;

        case 1: //call Dijkstra algorithm
            qInfo() << "Algorithm: Dijkstra, source:"<<origin_input->text()<<", destination:"<<destination_input->text();



            break;

        case 2: //call Astar algotithm
            qInfo() << "Algorithm: Astar, source:"<<origin_input->text()<<", destination:"<<destination_input->text();



            break;

        default:
            break;
    }
    displayed_graph->update();
    calculate_path_button->setChecked(false);
}
void View::reset_graph(){
    //Rest the graph to its original state
    reset_graph_button->setChecked(false);
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    // zoomSlider->setValue(250);
    // rotateSlider->setValue(0);
    // setupMatrix();
    // graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    // resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    // resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    // qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    // QTransform matrix;
    // matrix.scale(scale, scale);
    // matrix.rotate(rotateSlider->value());

    // graphicsView->setTransform(matrix);
    // setResetButtonEnabled();
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
#endif
}

void View::zoomIn()
{
    zoomSlider->setValue(zoomSlider->value() + 1);
}

void View::zoomOut()
{
    zoomSlider->setValue(zoomSlider->value() - 1);
}

void View::zoomInBy(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void View::zoomOutBy(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}













// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QWheelEvent>
// #include <QKeyEvent>
// #include <QToolButton>
// #include <QGridLayout>

// #include "View.h"


// View::View(QGraphicsScene* scene, QWidget *parent) : QGraphicsView(parent) {
//     setRenderHint(QPainter::Antialiasing);
//     setDragMode(QGraphicsView::RubberBandDrag);
//     setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//     setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//     setInteractive(true);
//     setWindowTitle(tr("Graph"));

//     setScene(scene);

//     // resetButton = new QToolButton;
//     // resetButton->setText(tr("0"));
//     // resetButton->setEnabled(false);

//     // QGridLayout *topLayout = new QGridLayout;
//     // topLayout->addWidget(resetButton, 2, 1);
//     // setLayout(topLayout);

//     // connect(resetButton, &QAbstractButton::clicked, this, &View::resetView);

//     QHBoxLayout *layout = new QHBoxLayout;
//     resetButton = new QToolButton;
//     resetButton->setText(tr("0"));
//     resetButton->setEnabled(false);
//     layout->addWidget(resetButton);

//     QGridLayout *topLayout = new QGridLayout;
//     topLayout->addLayout(layout, 0, 0);
//     // topLayout->addWidget(this, 1, 0);


//     setLayout(topLayout);

// }

// void View::resetView()
// {
//     // zoomSlider->setValue(250);
//     // rotateSlider->setValue(0);
//     setupMatrix();
//     ensureVisible(QRectF(0, 0, 0, 0));

//     resetButton->setEnabled(false);
// }
// void View::setResetButtonEnabled()
// {
//     resetButton->setEnabled(true);
// }
// void View::setupMatrix()
// {
//     qreal scale = qPow(qreal(2), (0 - 250) / qreal(50));

//     QTransform matrix;
//     matrix.scale(scale, scale);
//     matrix.rotate(0);

//     setTransform(matrix);
//     setResetButtonEnabled();
// }

// void View::wheelEvent(QWheelEvent *event) {
//     if(event->angleDelta().y() > 0)
//         scale(1.10, 1.10);
//     else
//         scale(0.9, 0.9);
// }

// void View::keyPressEvent(QKeyEvent *event) {
//     if(event->key() == Qt::Key_Left)
//         rotate(3);
//     else if(event->key() == Qt::Key_Right)
//         rotate(-3);
// }

