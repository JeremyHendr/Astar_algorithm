#include <QtWidgets>
#include <QtMath>

#include "view.h"
#include "Graph.h"



//--------------------------------------- user input handling ---------------------------------------//
void GraphicsView::wheelEvent(QWheelEvent *event) {
    /* handles the zoom
     *
     * @param event
    */
    if(event->angleDelta().y() > 0)
        scale(1.10, 1.10);
    else
        scale(0.9, 0.9);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    /* handle the mouse click event
     * Left click is the basic QGraphicsItem event
     * Right click has been reimplemented to select start and end nodes
     *
     *@param event
     */
    if (event->button() == Qt::RightButton) {

        QPoint mouse_pos_screen = QCursor::pos() - QPoint(20,70); //we apply a correction to have the true position
        QPoint mouse_pos_graph = displayed_graph->deviceTransform(viewportTransform()).inverted().map(mouse_pos_screen); //map the mouse position to the graph position
        // qInfo() << "Mouse position:" << QCursor::pos();
        // qInfo() << "Corresponding graph position:" << mouse_pos_graph;

        Vertex* vertex_at_mouse = displayed_graph->getClosestVertex(mouse_pos_graph);

        if (vertex_at_mouse != nullptr) {
            if (view->getOriginSelectionButton()->isChecked()) {
                QString previous_origin  = view->getOriginInput()->text(); //storing the last selected origin
                if (previous_origin != "") {
                    displayed_graph->getVertex(previous_origin.toUInt())->setState(VertexState::normal);
                }
                //change the start vertex state and wirte its ID in the start input
                vertex_at_mouse->setState(VertexState::start);
                view->getOriginInput()->clear();
                view->getOriginInput()->insert(QString::number(vertex_at_mouse->getID()));
                view->getOriginSelectionButton()->setChecked(false);
                view->getDestinationSelectionButton()->setChecked(true);
            }
            else {
                QString previous_destination  = view->getDestinationInput()->text();
                if (previous_destination != "") {
                    displayed_graph->getVertex(previous_destination.toUInt())->setState(VertexState::normal);
                }
                vertex_at_mouse->setState(VertexState::end);
                view->getDestinationInput()->clear();
                view->getDestinationInput()->insert(QString::number(vertex_at_mouse->getID()));
                view->getOriginSelectionButton()->setChecked(true);
                view->getDestinationSelectionButton()->setChecked(false);
            }
            // update the graph to show the flag
            displayed_graph->update();
            update();
        }
    }
    else {
        //This is the left click event
        QGraphicsView::mousePressEvent(event);
    }
}

//--------------------------------------- Input Validator ---------------------------------------//
QValidator::State VertexValidator::validate(QString &input, int &pos) const {
    /* Creates a list of all the vertices ID to later verify the inputs
     * See the QValidator for further informations */
    if (graph == nullptr) {
        // qInfo() << "Graph was not initialized in Validator";
        return Invalid;
    }
    else {
        if (input.toUInt() and graph->getVertex(input.toUInt()) != nullptr){
            // qInfo() << "acceptable";
            return Acceptable;
        }
        // qInfo() << "not acceptable";
        return Intermediate;
    }
}

//--------------------------------------- View class definition ---------------------------------------//
View::View(const QString &name, QWidget *parent) : QFrame(parent) {
    setFrameStyle(Panel | Plain);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
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
    input_range = new VertexValidator();
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

    //ORIGIN SELECTION BUTTON
    origin_selection_button = new QToolButton;
    origin_selection_button->setText(tr("Origin selection"));
    origin_selection_button->setCheckable(true);
    origin_selection_button->setChecked(true);
    vertex_selection->addWidget(origin_selection_button);

    //DESTINATION SELECTION BUTTON
    destination_selection_button = new QToolButton;
    destination_selection_button->setText(tr("Destination selection"));
    destination_selection_button->setCheckable(true);
    destination_selection_button->setChecked(false);
    vertex_selection->addWidget(destination_selection_button);

    //ALGORITHM SELECTION
    algorithm_selection = new QComboBox;
    algorithm_selection->addItem(tr("BFS"));
    algorithm_selection->addItem(tr("Dijkstra"));
    algorithm_selection->addItem(tr("Dijkstra_IPQ"));
    algorithm_selection->addItem(tr("Astar"));
    algorithm_selection->addItem(tr("Astar_IPQ"));
    vertex_selection->addWidget(algorithm_selection);


    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(vertex_selection, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    setLayout(topLayout);

    connect(reset_graph_button, &QAbstractButton::clicked, this, &View::reset_graph);
    connect(calculate_path_button, &QAbstractButton::clicked, this, &View::calculate_path);
    connect(origin_selection_button, &QAbstractButton::clicked, this, &View::change_selection);
    connect(destination_selection_button, &QAbstractButton::clicked, this, &View::change_selection);
}

void View::change_selection(){
    /* change the if we are selecting start or end node */
    origin_selection_button->setChecked(!origin_selection_button->isChecked());
    destination_selection_button->setChecked(!destination_selection_button->isChecked());
}

void View::calculate_path() {
    /* Call the selected algorithm if the inputs are valids */
    if (origin_input->hasAcceptableInput() && destination_input->hasAcceptableInput()) {
        // qInfo()<<"Acceptable input";
    }
    else {
        // qInfo()<<"Not acceptable input";
        calculate_path_button->setChecked(false);
        return;
    }

    uint32_t start = origin_input->text().toUInt();
    uint32_t end = destination_input->text().toUInt();
    reset_graph();
    switch(algorithm_selection->currentIndex()) {
        case 0: // Call BFS algorithm
            qInfo() << "Algorithm: BFS, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->BFS(start,end);
            break;

        case 1: // Call Dijkstra algorithm
            qInfo() << "Algorithm: Dijkstra, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->Dijkstra(start,end);
            break;

        case 2: // Call Astar algotithm
            qInfo() << "Algorithm: Dijkstra_IPQ, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->Dijkstra_IPQ(start,end);
            break;

        case 3: // Call Astar algotithm
            qInfo() << "Algorithm: Astar, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->A_star(start,end);
            break;

        case 4: // Call Astar algotithm
            qInfo() << "Algorithm: A_star_IPQ, source:"<<origin_input->text()<<", destination:"<<destination_input->text();
            displayed_graph->A_star_IPQ(start,end);
            break;

        default:
            break;
    }
    displayed_graph->update();
    calculate_path_button->setChecked(false);
}
void View::reset_graph(){
    //Reset the graph to its original state
    // qInfo()<<"Reset graph";
    displayed_graph->reset();
    displayed_graph->update();
    graphicsView->update();
    reset_graph_button->setChecked(false);
}

QGraphicsView *View::view() const {
    return static_cast<QGraphicsView *>(graphicsView);
}

