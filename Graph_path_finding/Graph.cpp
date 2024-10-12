/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file
* Contains method definition for the Graph class
*/


#include <unordered_map>
#include <QFile>
#include <QApplication>
#include <cstdint>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;



Graph::Graph(QString graph_data_file) {
    setFlags(ItemIsSelectable | ItemIsMovable);
    graph_name = graph_data_file;
    QFile file(graph_data_file);
    if(!file.open(QIODevice::ReadOnly)) {
        qInfo() << "Could not open file";
        qInfo() << file.errorString();
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields[0] == "V") { //V,vertexid,longitude,latitude,x*,y*
            const uint32_t ID = fields[1].toUInt();
            const float longitude = fields[2].toFloat();
            const float latitude = fields[3].toFloat();

            if (fields[4] != ""){ // Check if we have values for x and y
                const int x = fields[4].toInt();
                const int y = fields[5].toInt();
                Vertex* v = new Vertex(ID, x, y);
                addVertex(v);

            }
            else{
                Vertex* v = new Vertex(ID, longitude, latitude);
                addVertex(v);
            }

        }

        else if (fields[0] == "E") { //E,source_id,dest_id,length,name
            uint32_t source_ID = fields[1].toUInt();
            uint32_t dest_ID = fields[2].toUInt();
            double length = fields[3].toDouble();
            string name = fields[4].toStdString();
            Edge* e;

            if (fields[4].toStdString() != "???"){ // A real name has been given
                bool name_given = true;
                e = new Edge(source_ID, dest_ID, length, name, name_given);
            }
            else{ // No name indicated ("???")
                bool name_given = false;
                e = new Edge(source_ID, dest_ID, length, name, name_given);
            }
            addEdge(e);

            // Get source vertex
            // Add to neighbor the dest vertex
            // Add the edge in the pair
        }
    }

    file.close();

    // Read the edge_map and add the neighbors to the corresponding vertices
    for (const auto& pair: edges_map){
        Edge* e = pair.second;
        uint32_t source_id = e->getSourceId();
        uint32_t dest_id = e->getDestinationId();

        Vertex* source_v = getVertex(source_id);
        Vertex* dest_v = getVertex(dest_id);
        e->setCoordinates(source_v->getCoordinate(), dest_v->getCoordinate());

        std::pair<Vertex*, Edge*> neighbor(dest_v, e);
        source_v->addNeighbor(neighbor);
    }

    print();
}

QRectF Graph::boundingRect() const
{
    return QRectF(-10000, -10000, 50000, 50000);
}


void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    QPen* pen = new QPen();
    pen->setWidth(5);
    pen->setColor(Qt::white);
    painter->setPen(*pen);

    for (const auto pair : edges_map) {
        const QPoint* source = pair.second->getSourceCoordinate();
        const QPoint* destination = pair.second->getDestinationCoordinate();;
        painter->drawLine(source->x(),source->y(),destination->x(),destination->y());
    }
}


void Graph::addVertex(Vertex* v){
    /* Add vertices to the vertices_map
     *
     * @param Takes a vertex v
     * @return
     */
    vertices_map.insert({v->getID(), v});
}


void Graph::addEdge(Edge* e){
    /* Add edges to the edges_map
     *
     * @param Takes an edge e
     * @return
     */
    edges_map.insert({e->getID(), e});
}


void Graph::print() const{
    /* Print graph description
     */
    qInfo() << "Graph with " << vertices_map.size() << " vertices and " << edges_map.size() << " edges";
}


Vertex* Graph::getVertex(uint32_t id) {
    /* Retrieve vertex by id
     *
     * @param id
     * @return vertex
     */
    if (vertices_map.find(id) == vertices_map.end()) {
        qInfo() << "No Vertex with id" << id;
        return nullptr;
    }
    return vertices_map.at(id);
}


Edge* Graph::getEdge(string id) {
    /* Retrieve edge by id
     *
     * @param id
     * @return edge
     */
    auto it = edges_map.find(id);
    if (it != edges_map.end()) {
        return it->second;
    }
    else {
        return nullptr; // Return nullptr if the edge is not found
    }
}

void Graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Graph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Graph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}


// vector<Vertex*> Graph::BFS(Vertex* origin, Vertex* destination, bool time){
//     // Method for the BFS algorithm
//     //TODO
// }

// void Graph::populateScene() {
//     GraphPath* g = new GraphPath(&edges_map);
//     addItem(g);


//     // QList<QGraphicsItem*> edge_list;
//     // for (const auto pair : edges_map) {
//     //     edge_list.append(pair.second);
//     // }
//     // QGraphicsItemGroup *group = createItemGroup(edge_list);



//     // for (const auto pair : vertices_map){
//     //     addItem(pair.second);
//     // }

//     // for (const auto pair : edges_map) {
//     //     addItem(pair.second);
//     // }

//     qInfo() << "Finished populating scene.";
// }
