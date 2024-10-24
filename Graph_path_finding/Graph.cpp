/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file
* Contains method definition for the Graph class
*/

#include <QFile>
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <unordered_map>
#include <iostream>
#include <regex>
#include <queue>
#include <chrono>
#include <cstdint>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Commify.h"
#include "Ipq.h"

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
            string name = fields[4].toStdString();
            Edge* e;
            double length = 0;
            bool name_given;

            if (fields[3] == ""){ // No length was provided / needs to be computed from projected source and destination
                double x_source = getVertex(source_ID)->getCoordinate()->x(); // Get x coordinate of source vertex which is stored in a QPoint
                double y_source = getVertex(source_ID)->getCoordinate()->y();
                double x_dest = getVertex(dest_ID)->getCoordinate()->x();
                double y_dest = getVertex(dest_ID)->getCoordinate()->y();
                length = sqrt(pow((x_source-x_dest),2) + pow((y_source-y_dest),2)); // Compute length i.e. weight
            }
            else{ // Length was provided
                length = fields[3].toDouble();
            }

            regex question_mark_pattern(R"(\?+)");

            // fields[4].toStdString() != "???"
            if (!regex_match(fields[4].toStdString(), question_mark_pattern)){ // A real name has been given
                name_given = true;
                //e = new Edge(source_ID, dest_ID, length, name, name_given, length_given);
            }
            else{ // No name indicated ("???")
                name_given = false;
                //e = new Edge(source_ID, dest_ID, length, name, name_given, length_given);
            }

            e = new Edge(source_ID, dest_ID, length, name, name_given);

            addEdge(e);
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
        e->setPoints(*source_v->getCoordinate(), *dest_v->getCoordinate());

        std::pair<Vertex*, Edge*> neighbor(dest_v, e);
        source_v->addNeighbor(neighbor);
    }

    print();
}

QRectF Graph::boundingRect() const {
    return QRectF(-10000, -10000, 50000, 50000);
}


void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    //We first draw the standard lines and finally
    //the visited one and then the mainpath.
    //this is done to avoid white lines overlaying the red or green ones
    QList<Edge*> mainpath_edges;
    QList<Edge*> visited_edges;
    for (const auto &pair : edges_map) {
        Edge* e = pair.second;
        switch (e->getState()) {
        case EdgeState::normal:
            painter->setPen(*e->getPen());
            painter->drawLine(*e);
            break;
        case EdgeState::visited:
            visited_edges.append(e);
            break;
        case EdgeState::mainpath:
            mainpath_edges.append(e);
            break;
        }
    }
    for (const auto e : visited_edges) {
        painter->setPen(*e->getPen());
        painter->drawLine(*e);
    }
    for (const auto e : mainpath_edges) {
         painter->setPen(*e->getPen());
         painter->drawLine(*e);
    }


    for (const auto pair : vertices_map) {
        Vertex* v = pair.second;
        painter->setPen(*v->getPen());
        painter->setBrush(*v->getBrush());
        painter->drawEllipse(*v->getCoordinate(),v->getEllipseSize(),v->getEllipseSize());
    }
}

void Graph::reset(){
    for (const auto& pair : edges_map) {
        pair.second->setState(EdgeState::normal);
    }
    for (const auto pair : vertices_map) {
        pair.second->setState(VertexState::normal);
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

//--------------------------------------- BFS ---------------------------------------//

void Graph::BFS(uint32_t start, uint32_t end){
    /* Perform the BFS algorithm on the unweighted graph
     *
     * @param Vertex* start, Vertex* end
     * @return
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();


    int visited_count = 0;
    queue<Vertex*> active_queue; // Active queue of nodes to visit ( O(1) complexity for insertion)
    unordered_map<uint32_t, bool> visited; // Unordered map with vertex id and bool to indicate visitation status
    unordered_map<Vertex*, Vertex*> parent; // Parent map to store the parent of each visited vertex
    parent[getVertex(start)] = nullptr;

    for (const auto& elem: vertices_map){ // Construct the visited vector with the id of a vertex and set the status for each vector to false
        visited.insert({elem.first, false});
    }

    active_queue.push(getVertex(start)); // Initialize queue with start vertex
    visited[start] = true; // Change the status of the start vertex to visited

    // BFS Loop
    while (!active_queue.empty()){
        Vertex* v = active_queue.front(); // Get the first vertex in the queue to visit
        active_queue.pop(); // Remove the current element from the queue as we are visiting it

        // If we have reached the end vertex, stop the search
        if (v == getVertex(end)){
            break;
        }

        bool isDeadEnd = true; // Assume vertex is a dead end unless proven otherwise

        for(const auto& neighbor: v->getNeighbors()){
            uint32_t neighborID = neighbor.first->getID();
            if (visited.find(neighborID) != visited.end() && visited[neighborID] == false){ // Vertex has not been visited yet
                active_queue.push(neighbor.first); // Add the neighbor to the end of the active queue
                visited[neighborID] = true; // Set status to visited
                visited_count++;
                parent[neighbor.first] = v; // Add the neighbor and the vertex to the parent map to reconstruct path

                // Set status of edge to visited
                string id = to_string(v->getID()) + "." + to_string(neighbor.first->getID());
                getEdge(id)->setState(EdgeState::visited);

                // Set state of vertex to visited
                neighbor.first->setState(VertexState::visited);

                // Since we found an unvisited neighbor, this vertex is not a dead end
                isDeadEnd = false;
            }
        }

        // After checking all neighbors, if no unvisited neighbors were found, mark the vertex as a dead end
        if (isDeadEnd){
            v->setState(VertexState::deadend);
        }
    }

    // Mark the remaining vertices as dead ends (in the case of the search although on the map they may not appear to be dead ends
    while(!active_queue.empty()){
        active_queue.front()->setState(VertexState::deadend);
        active_queue.pop();
    }

    // Reconstruct the path backwards starting from the end
    Vertex* prevVertex = nullptr;
    for (Vertex* at = getVertex(end); at != nullptr; at = parent[at]){
        if (prevVertex != nullptr){
            // If we create id like usual, it will be inverted since we go from the end vertex to start
            // We therefore need to create the id the from end vertex id to start vertex id to have the correct edge
            string id = to_string(at->getID()) + "." + to_string(prevVertex->getID());
            getEdge(id)->setState(EdgeState::mainpath);
            // Set state of vertex which is on the mainpath
            at->setState(VertexState::mainpath);
        }
        prevVertex = at; // Set the previous vertex to the current one as we have already used it
        BFS_path.push_back(at); // Create the shortest path
    }

    // Reverse the shortest path so it goes from start to end
    reverse(BFS_path.begin(), BFS_path.end());

    // Set state of start and end vertices
    BFS_path.front()->setState(VertexState::start);
    BFS_path.back()->setState(VertexState::end);


    // End time measurement
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> BFS_duration = end_time - start_time;

    // Return shortest path if start and end are connected
    if (!BFS_path.empty() && BFS_path.front() == getVertex(start)){
        printShortestPath(BFS_path, visited_count, BFS_duration, "BFS");
    }
    else{ // Start and end are not connected
        qInfo() << "No connection between start and end vertices";
    }
}

vector<Vertex*> Graph::getBFSPath(){
    /* Retrieve computed BFS shortest path
     *
     * @return vector<Vertex*> BFS_path
     */
    return BFS_path;
}


//--------------------------------------- Dijkstra ---------------------------------------//

// Custom Comparator for Min-Heap for Dijkstra
struct CompareDist {
    bool operator()(const std::pair<uint32_t, double>& p1, const std::pair<uint32_t, double>& p2) {
        // We want the smallest distance to have the highest priority (min-heap behavior)
        return p1.second > p2.second;
    }
};

void Graph::Dijkstra(uint32_t start, uint32_t end){
    /* Perform the Dijkstra algorithm on the weighted graph
     *
     * @param Vertex* start, Vertex* end
     * @return
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();


    int visited_count = 0; // Keep track of the number of visited vertices

    unordered_map<uint32_t, bool> visited; // Unordered map with vertex id and bool to indicate visitation status
    unordered_map<uint32_t, double> dist; // Keeps track of the distance for each vertex
    unordered_map<uint32_t, uint32_t> parent; // Stores the parents to reconstruct the path

    // Populate the maps
    for (const auto& elem: vertices_map){
        visited[elem.first] = false; // Set the visited status of all vertices in the graph to false
        dist[elem.first] = numeric_limits<double>::infinity(); // Set the distance/weight to infinity for each vertex
        parent[elem.first] = -1; // Initialize parent to -1 (undefined)
    }

    dist[start] = 0; // Set the distance for the start vertex to 0

    // Define the priority queue and its elements
    typedef pair<uint32_t, double> pii; // First: vertex id / Second: distance
    priority_queue<pii, vector<pii>, CompareDist> pq; // Create the priority queue with a custom Compare method to get a Min-Heap
    pq.push({start, 0}); // Add the start vector with the 0 distance to the pq


    // Dijkstra's loop
    while (!pq.empty()){
        // Remove the next most promising vertex / min distance pair
        uint32_t current_v_id = pq.top().first;
        double current_v_dist = pq.top().second;
        pq.pop(); // Remove the current vertex from the pq since we visited it

        if (visited[current_v_id]) continue; // Skip the vertex if already visited
        visited[current_v_id] = true; // Mark current vertex as visited

        if (current_v_id == end) break; // The end vertex has been found

        bool isDeadEnd = true;
        // Explore the neighbors
        for (const auto& neighbor: getVertex(current_v_id)->getNeighbors()){
            uint32_t neighborID = neighbor.first->getID();

            if (visited[neighborID]) continue;

            // Recreate edge id to get the weight
            string id = to_string(current_v_id) + "." + to_string(neighborID);
            double edge_weight = getEdge(id)->getLength();

            // Get the weight of the path to the current vertex and add the weight from the current vertex to its neighbor to get the total distance to start
            double new_dist = current_v_dist + edge_weight;

            if (new_dist < dist[neighborID]){ // If new distance is less than the distance of the neighbor to the start
                dist[neighborID] = new_dist; // Update value to vertex if it is better
                pq.push({neighborID, new_dist}); // Insert new key - value pair into to queue so that we visit this vertex in the future
                parent[neighborID] = current_v_id;
                visited_count++;

                // Set edge status to visited
                string id = to_string(getVertex(current_v_id)->getID()) + "." + to_string(neighbor.first->getID());
                getEdge(id)->setState(EdgeState::visited);

                // Set vertex status
                getVertex(neighborID)->setState(VertexState::visited);

                // Unvisited neighbor found = not a dead end
                isDeadEnd = false;
            }
        }

        // After checking all neighbors, if no unvisited neighbors were found, mark the vertex as a dead end
        if (isDeadEnd){
            getVertex(current_v_id)->setState(VertexState::deadend);
        }
    }

    // Mark the remaining vertices as dead ends (in the case of the search although on the map they may not appear to be dead ends
    while(!pq.empty()){
        getVertex(pq.top().first)->setState(VertexState::deadend);
        pq.pop();
    }

    // Reconstruct the path from end to start
    Vertex* prevVertex = nullptr;
    for (uint32_t at = end; at != -1; at = parent[at]){
        if (prevVertex != nullptr){
            // If we create id like usual, it will be inverted since we go from the end vertex to start
            // We therefore need to create the id the from end vertex id to start vertex id to have the correct edge
            string id = to_string(getVertex(at)->getID()) + "." + to_string(prevVertex->getID());
            getEdge(id)->setState(EdgeState::mainpath);
            // Set state of vertex which is on the mainpath
            getVertex(at)->setState(VertexState::mainpath);
        }
        prevVertex = getVertex(at);
        dijkstra_path.push_back(getVertex(at));
    }

    // Reverse the shortest path so it goes from start to end
    reverse(dijkstra_path.begin(), dijkstra_path.end());

    // Set state of start and end vertices
    dijkstra_path.front()->setState(VertexState::start);
    dijkstra_path.back()->setState(VertexState::end);

    // End time measurement
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> dijkstra_duration = end_time - start_time;

    // Return shortest path if start and end are connected
    if (!dijkstra_path.empty() && dijkstra_path.front() == getVertex(start)){
        printShortestPath(dijkstra_path, visited_count, dijkstra_duration, "Dijkstra");
    }
    else{ // Start and end are not connected
        qInfo() << "No connection between start and end vertices";
    }
}

vector<Vertex*> Graph::getDijkstraPath(){
    /* Retrieve computed Dijkstra shortest path
     *
     * @return vector<Vertex*> dijkstra_path
     */
    return dijkstra_path;
}


void Graph::Dijkstra_IPQ(uint32_t start, uint32_t end){
    /* Perform the Dijkstra algorithm on the weighted graph
     *
     * @param Vertex* start, Vertex* end
     * @return
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();


    int visited_count = 0; // Keep track of the number of visited vertices

    unordered_map<uint32_t, bool> visited; // Unordered map with vertex id and bool to indicate visitation status
    unordered_map<uint32_t, double> dist; // Keeps track of the distance for each vertex
    unordered_map<uint32_t, uint32_t> parent; // Stores the parents to reconstruct the path

    // Populate the maps
    for (const auto& elem: vertices_map){
        visited[elem.first] = false; // Set the visited status of all vertices in the graph to false
        dist[elem.first] = numeric_limits<double>::infinity(); // Set the distance/weight to infinity for each vertex
        parent[elem.first] = -1; // Initialize parent to -1 (undefined)
    }

    dist[start] = 0; // Set the distance for the start vertex to 0

    // Define the priority queue and its elements
    //typedef pair<uint32_t, double> pii; // First: vertex id / Second: distance
    //priority_queue<pii, vector<pii>, CompareDist> pq; // Create the priority queue with a custom Compare method to get a Min-Heap
    //pq.push({start, 0}); // Add the start vector with the 0 distance to the pq

    Ipq ipq(vertices_map.size());
    ipq.insert(start, 0);

    // Dijkstra's loop
    while (!ipq.isEmpty()){
        // Remove the next most promising vertex / min distance pair
        uint32_t current_v_id = ipq.popMin();
        double current_v_dist = dist[current_v_id];
        //pq.pop(); // Remove the current vertex from the pq since we visited it

        if (visited[current_v_id]) continue; // Skip the vertex if already visited
        visited[current_v_id] = true; // Mark current vertex as visited

        if (current_v_id == end) break; // The end vertex has been found

        bool isDeadEnd = true;
        // Explore the neighbors
        for (const auto& neighbor: getVertex(current_v_id)->getNeighbors()){
            uint32_t neighborID = neighbor.first->getID();

            if (visited[neighborID]) continue;

            // Recreate edge id to get the weight
            string id = to_string(current_v_id) + "." + to_string(neighborID);
            double edge_weight = getEdge(id)->getLength();

            // Get the weight of the path to the current vertex and add the weight from the current vertex to its neighbor to get the total distance to start
            double new_dist = current_v_dist + edge_weight;

            if (new_dist < dist[neighborID]){ // If new distance is less than the distance of the neighbor to the start
                dist[neighborID] = new_dist; // Update value to vertex if it is better
                //pq.push({neighborID, new_dist}); // Insert new key - value pair into to queue so that we visit this vertex in the future
                parent[neighborID] = current_v_id;

                if (ipq.contains(neighborID)){
                    ipq.decreaseKey(neighborID, new_dist);
                }
                else {
                    ipq.insert(neighborID, new_dist);
                }

                visited_count++;

                // Set edge status to visited
                string id = to_string(getVertex(current_v_id)->getID()) + "." + to_string(neighbor.first->getID());
                getEdge(id)->setState(EdgeState::visited);

                // Set vertex status
                getVertex(neighborID)->setState(VertexState::visited);

                // Unvisited neighbor found = not a dead end
                isDeadEnd = false;
            }
        }

        // After checking all neighbors, if no unvisited neighbors were found, mark the vertex as a dead end
        if (isDeadEnd){
            getVertex(current_v_id)->setState(VertexState::deadend);
        }
    }

    // Mark the remaining vertices as dead ends (in the case of the search although on the map they may not appear to be dead ends
    while(!ipq.isEmpty()){
        getVertex(ipq.popMin())->setState(VertexState::deadend);
        //pq.pop();
    }

    // Reconstruct the path from end to start
    Vertex* prevVertex = nullptr;
    for (uint32_t at = end; at != -1; at = parent[at]){
        if (prevVertex != nullptr){
            // If we create id like usual, it will be inverted since we go from the end vertex to start
            // We therefore need to create the id the from end vertex id to start vertex id to have the correct edge
            string id = to_string(getVertex(at)->getID()) + "." + to_string(prevVertex->getID());
            getEdge(id)->setState(EdgeState::mainpath);
            // Set state of vertex which is on the mainpath
            getVertex(at)->setState(VertexState::mainpath);
        }
        prevVertex = getVertex(at);
        dijkstra_path.push_back(getVertex(at));
    }

    // Reverse the shortest path so it goes from start to end
    reverse(dijkstra_path.begin(), dijkstra_path.end());

    // Set state of start and end vertices
    dijkstra_path.front()->setState(VertexState::start);
    dijkstra_path.back()->setState(VertexState::end);

    // End time measurement
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> dijkstra_duration = end_time - start_time;

    // Return shortest path if start and end are connected
    if (!dijkstra_path.empty() && dijkstra_path.front() == getVertex(start)){
        printShortestPath(dijkstra_path, visited_count, dijkstra_duration, "Dijkstra");
    }
    else{ // Start and end are not connected
        qInfo() << "No connection between start and end vertices";
    }
}


//--------------------------------------- A* ---------------------------------------//








//--------------------------------------- Path Printing ---------------------------------------//
void Graph::printShortestPath(vector<Vertex*> path,int total_visited_vertex, chrono::duration<double, std::micro> duration, string algorithm){
    /* Display the shortest path computed with the choosen algorithm
     */

    cout << "Shortest path computed with " << algorithm << endl;
    cout << "Total visited vertices = " << total_visited_vertex << endl;
    cout << "Total vertices on path from start to end = " << path.size() << endl;

    int cnt = 1; // Vertex counter
    double length = 0.0;
    Vertex* prevVertex = nullptr;

    for (const auto& element: path){
        if (prevVertex != nullptr){ // Recreate id and get the length
            string id = to_string(prevVertex->getID()) + "." + to_string(element->getID());
            length += getEdge(id)->getLength();
        }

        // Create trace output
        cout << "Vertex[ " << setw(4) << cnt
             << "] = " << setw(10) << element->getID()
             << ", length = " << setw(10) << fixed << setprecision(2) << length << endl;

        cnt++;
        prevVertex = element; // Save previous vertex
    }

    cout << "Path total length: " << length << " m" << endl;
    cout << "INFO: path calculated in " << Commify(duration.count()) << "us" << endl;
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
