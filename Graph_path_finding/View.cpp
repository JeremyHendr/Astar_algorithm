#include <QtWidgets>
#include <QtMath>

#include "view.h"

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


    QHBoxLayout *vertex_selection = new QHBoxLayout;

    //RESET BUTTON
    reset_graph_button = new QToolButton;
    reset_graph_button->setText(tr("Reset graph"));
    reset_graph_button->setCheckable(true);
    reset_graph_button->setChecked(false);
    vertex_selection->addWidget(reset_graph_button);

    //CALCULATE PATH BUTTON
    calculate_path_button = new QToolButton;
    calculate_path_button->setText(tr("Calculate"));
    calculate_path_button->setCheckable(true);
    calculate_path_button->setChecked(false);
    vertex_selection->addWidget(calculate_path_button);

    //VERTEX INPUT
    input_range = new QIntValidator(0,999999);
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

    //ALGORITHM SELECTION
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
}


void View::calculate_path() {
    if (origin_input->hasAcceptableInput() && destination_input->hasAcceptableInput()) {
        qInfo()<<"Acceptable input";
    }
    else {
        qInfo()<<"Not acceptable input";
        calculate_path_button->setChecked(false);
        return;
    }

    uint32_t start = origin_input->text().toUInt(); //86771;
    uint32_t end = destination_input->text().toUInt(); //110636;81615

    switch(algorithm_selection->currentIndex()) {
        case 0: //call BFS algotithm
            qInfo() << "Algorithm: BFS, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->BFS(start,end);


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
    qInfo()<<"Reset graph";
    displayed_graph->reset();
    reset_graph_button->setChecked(false);
}

QGraphicsView *View::view() const {
    return static_cast<QGraphicsView *>(graphicsView);
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

