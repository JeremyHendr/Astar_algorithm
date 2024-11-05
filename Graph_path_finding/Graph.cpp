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
#include <set>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Commify.h"
#include "Ipq.h"

using namespace std;

void drawFlag(QPainter* painter, QPoint* pos, int pole_height, QColor flag_color) {
    /* This function is provided for conveniency,
     * it draws a flag that scales in size proportionnaly to the pole size
     *
     * @param painter used to draw the flag
     * @param pos start coordinates of the pole
     * @param pole_height
     * @param flag_color
     */
    int x = pos->x();
    int y = pos->y();

    // Define the scaling factor based on the pole height
    float scale = pole_height / 100.0f;  // 100 is the base height for reference

    // Calculate the pole width and flag dimensions based on the scale
    int pole_width = static_cast<int>(5 * scale);
    int flag_width = static_cast<int>(40 * scale);
    int flag_height = static_cast<int>(25 * scale);
    int wave_offset = static_cast<int>(10 * scale);

    // Draw the pole
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(x, y - pole_height, pole_width, pole_height);

    // Draw the flag with waving effect
    QPolygon flag_shape;
    flag_shape << QPoint(x + pole_width, y - pole_height)
               << QPoint(x + pole_width + flag_width, y - pole_height + wave_offset)
               << QPoint(x + pole_width + flag_width, y - pole_height + flag_height - wave_offset)
               << QPoint(x + pole_width, y - pole_height + flag_height);

    painter->setBrush(flag_color);
    painter->drawPolygon(flag_shape);
}

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
            Vertex* v;
            if (fields[4] != ""){ // Check if we have values for x and y
                const float longitude = fields[2].toFloat();
                const float latitude = fields[3].toFloat();
                const int x = fields[4].toInt();
                const int y = fields[5].toInt();
                v = new Vertex(ID, longitude, latitude, x, y);
                addVertex(v);

            }
            else{
                const float longitude = fields[2].toFloat();
                const float latitude = fields[3].toFloat();
                v = new Vertex(ID, longitude, latitude);
                addVertex(v);
            }
            if (v->getCoordinate()->x() < top_left_coord->x()) {
                top_left_coord->setX(v->getCoordinate()->x());
            }
            if (v->getCoordinate()->y() < top_left_coord->y()) {
                top_left_coord->setY(v->getCoordinate()->y());
            }
            if (v->getCoordinate()->x() > bottom_right_coord->x()) {
                bottom_right_coord->setX(v->getCoordinate()->x());
            }
            if (v->getCoordinate()->y() > bottom_right_coord->y()) {
                bottom_right_coord->setY(v->getCoordinate()->y());
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
    return QRectF(  top_left_coord->x(),
                    top_left_coord->y(),
                    bottom_right_coord->x()-top_left_coord->x(),
                    bottom_right_coord->y()-top_left_coord->y());
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

    Vertex* start=nullptr;
    Vertex* end=nullptr;
    for (const auto pair : vertices_map) {
        Vertex* v = pair.second;
        painter->setPen(v->getPen());
        painter->setBrush(v->getBrush());
        painter->drawEllipse(*v->getCoordinate(),v->getEllipseSize(),v->getEllipseSize());

        if (v->getState() == VertexState::start) {
            start = v;
        }
        else if (v->getState() == VertexState::end) {
            end = v;
        }
    }
    if (start!=nullptr) {
        drawFlag(painter, start->getCoordinate(), 600, Qt::green);
    }
    if (end!=nullptr) {
        drawFlag(painter, end->getCoordinate(), 600, Qt::red);
    }

    //Draw the selection of the graph
    painter->setBrush(QBrush());
    painter->setPen(QPen(Qt::white, 10));
    painter->drawRect(  top_left_coord->x(),
                        top_left_coord->y(),
                        bottom_right_coord->x()-top_left_coord->x(),
                        bottom_right_coord->y()-top_left_coord->y());
}


void Graph::reset(){
    for (const auto& pair : edges_map) {
        pair.second->setState(EdgeState::normal);
    }
    for (const auto pair : vertices_map) {
        if (pair.second->getState() != VertexState::start and pair.second->getState() != VertexState::end) {
            pair.second->setState(VertexState::normal);
        }
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


Vertex* Graph::getVertex(QPoint p) {
    QPoint z;
    Vertex* closestVertex = nullptr;
    int minDistanceSquared = 500 * 500; // Square of the range limit to avoid calculating square roots

    for (auto pair : vertices_map) {
        z = *pair.second->getCoordinate() - p;

        // Check if the vertex is within the 100x100 range
        if (abs(z.x()) < 500 && abs(z.y()) < 500) {
            int distanceSquared = z.x() * z.x() + z.y() * z.y();

            // Update closestVertex if this vertex is closer
            if (distanceSquared < minDistanceSquared) {
                minDistanceSquared = distanceSquared;
                closestVertex = pair.second;
            }
        }
    }

    return closestVertex;
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

//--------------------------------------- Custom Comparator for Min-Heap ---------------------------------------//
struct CompareDist {
    /* Structure for the Priority Queues to get the Min-Heap
     */

    bool operator()(const std::pair<uint32_t, double>& p1, const std::pair<uint32_t, double>& p2) {
        // We want the smallest distance to have the highest priority (min-heap behavior)
        return p1.second > p2.second;
    }
};

//--------------------------------------- BFS ---------------------------------------//
void Graph::BFS(uint32_t start, uint32_t end){
    /* Perform the BFS algorithm on the unweighted graph and print the result in the console
     *
     * @param uint32_t start, uint32_t end
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();

    // Free the memory so that the old path is overridden
    BFS_path.clear();

    int visited_count = 0;

    queue<Vertex*> active_queue; // Active queue of nodes to visit ( O(1) complexity for insertion)
    unordered_map<uint32_t, bool> visited; // Unordered map with vertex id and bool to indicate visitation status
    unordered_map<uint32_t, uint32_t> parent; // Parent map to store the parent of each visited vertex

    for (const auto& elem: vertices_map){ // Construct the visited vector with the id of a vertex and set the status for each vector to false
        visited[elem.first] = false;
        parent[elem.first] = numeric_limits<uint32_t>::infinity();
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
                ++visited_count;
                parent[neighborID] = v->getID(); // Add the neighbor and the vertex to the parent map to reconstruct path

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
    BFS_path = reconstructShortestPath(start, end, parent);

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
void Graph::Dijkstra(uint32_t start, uint32_t end){
    /* Perform the Dijkstra algorithm on the weighted graph using a Priority Queue and print the result in the console
     *
     * @param uint32_t start, uint32_t end
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();

    // Free the memory so that the old path is overridden
    dijkstra_path.clear();

    int visited_count = 0; // Keep track of the number of visited vertices

    unordered_map<uint32_t, bool> visited; // Unordered map with vertex id and bool to indicate visitation status
    unordered_map<uint32_t, double> dist; // Keeps track of the distance for each vertex
    unordered_map<uint32_t, uint32_t> parent; // Stores the parents to reconstruct the path

    // Populate the maps
    for (const auto& elem: vertices_map){
        visited[elem.first] = false; // Set the visited status of all vertices in the graph to false
        dist[elem.first] = numeric_limits<double>::infinity(); // Set the distance/weight to infinity for each vertex
        //parent[elem.first] = -1; // Initialize parent to -1 (undefined)
        parent[elem.first] = numeric_limits<uint32_t>::infinity();
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

        if (current_v_id == end) break; // The end vertex has been found

        if (visited[current_v_id]) continue; // Skip the vertex if already visited
        visited[current_v_id] = true; // Mark current vertex as visited
        ++visited_count;

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
    dijkstra_path = reconstructShortestPath(start, end, parent);

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


void Graph::Dijkstra_IPQ(uint32_t start, uint32_t end){
    /* Perform the Dijkstra algorithm on the weighted graph using an Indexed Priority Queue and print the result in the console
     *
     * @param uint32_t start, uint32_t end
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();

    // Free the memory so that the old path is overridden
    dijkstra_path.clear();

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

    Ipq ipq(vertices_map.size()); // Create the Index Priority Queue object
    ipq.insert(start, 0); // Add the start vertex

    // Dijkstra's loop
    while (!ipq.isEmpty()){
        // Remove the next most promising vertex / min distance pair
        uint32_t current_v_id = ipq.popMin();
        double current_v_dist = dist[current_v_id];

        if (visited[current_v_id]) continue; // Skip the vertex if already visited
        visited[current_v_id] = true; // Mark current vertex as visited
        ++visited_count;

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
                parent[neighborID] = current_v_id;

                // Check if the neighbor is already in the IPQ and treat the corresponding case
                if (ipq.contains(neighborID)){
                    ipq.decreaseKey(neighborID, new_dist);
                }
                else {
                    ipq.insert(neighborID, new_dist);
                }

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
    }

    // Reconstruct the path from end to start
    dijkstra_path = reconstructShortestPath(start, end, parent);

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

//--------------------------------------- A* ---------------------------------------//
double Graph::heuristic(uint32_t vertexA, uint32_t vertexB) {
    /* Heuristic for the A* algorithm.
     * In this case we use the Haversine formula which uses the longitude and latitude coordinates of the vertices
     *
     * @param uint32_t a, uint32_t b (2 vertex ids)
     * @return double (distance estimation)
     */

    // Get the longitude and lattitude for each vertex and convert them to radians
    double lat1 = (getVertex(vertexA)->latitude)* M_PI / 180.0;
    double lon1 = (getVertex(vertexA)->longitude)* M_PI / 180.0;
    double lat2 = (getVertex(vertexB)->latitude)* M_PI / 180.0;
    double lon2 = (getVertex(vertexB)->longitude)* M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1; // Delta Latitude
    double dLon = lon2 - lon1; // Delta Longitude

    double e = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(e), std::sqrt(1 - e));

    double R = 6371.0; // Radius of Earth in kilometers
    return R * c; // Distance in kilometers between the two vertices
}


void Graph::A_star(uint32_t start, uint32_t end){
    /* Perform the A* algorithm on the weighted graph using a Priority Queue and a heuristic function (Haversine Formula Distance) and print the result in the console
     * We used the Haversine formula since it uses the latitude and longitude of the vertices and is therefore invariant to the mercator projection
     *
     * @param uint32_t start, uint32_t end
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();

    // Free the memory so that the old path is overridden
    astar_path.clear();

    int visited_count = 0; // Track the number of visited vertices

    // Define the priority queue with A* cost (g + h) and its elements
    typedef pair<uint32_t, double> pii; // First: vertex id / Second: distance
    priority_queue<pii, vector<pii>, CompareDist> openSet; // Create the priority queue with a custom Compare method to get a Min-Heap

    // Set (log(N) complexity) for visited vertices
    std::set<uint32_t> closed_set;

    // Define and populate the maps
    unordered_map<uint32_t, double> gScore;
    unordered_map<uint32_t, double> fScore;
    unordered_map<uint32_t, uint32_t> parent; // Parent map to record the best path (Key: neighbor vertex ; Value: current vertex) O(1) complexity

    for (const auto& elem: vertices_map){
        gScore[elem.first] = numeric_limits<double>::infinity();
        fScore[elem.first] = numeric_limits<double>::infinity();
        parent[elem.first] = numeric_limits<uint32_t>::infinity();
    }

    gScore[start] = 0; // The start node has a g cost of 0
    fScore[start] = heuristic(start,end); // The start node has a f cost of the heuristic from start to end (h = f + g but g = 0 in this case)

    openSet.push({start,fScore[start]}); // Add the start vector with the 0 distance to the pq

    // A* loop
    while (!openSet.empty()){
        uint32_t current = openSet.top().first; // Get the next most promising vertex based on cost
        openSet.pop(); // Remove the current vertex from the queue

        if (closed_set.find(current) != closed_set.end()) continue;

        closed_set.insert(current); // Add the current vertex to the visited ones
        ++visited_count;

        if (current == end) break; // If the end vertex was found, we stop

        bool isDeadEnd = true;

        // Explore the neighbors of the current vertex
        for (const auto& neighbor: getVertex(current)->getNeighbors()){
            uint32_t neighborID = neighbor.first->getID();

            if (closed_set.find(neighborID) != closed_set.end()) continue;

            // Get the edge from the current vertex to the neighbor and compute the tentative g score
            string id = to_string(getVertex(current)->getID()) + "." + to_string(neighbor.first->getID());
            auto tentative_gScore = gScore[current] + getEdge(id)->getLength();

            if (tentative_gScore < gScore[neighborID]){ // If the score is less than the current one saved for the neighbor, update everything accordingly
                parent[neighborID] = current; // New shortest node found, add to saved path
                gScore[neighborID] = tentative_gScore;
                fScore[neighborID] = tentative_gScore + heuristic(neighborID, end);

                openSet.push({neighborID, fScore[neighborID]});

                // Set edge and vertex status
                getEdge(id)->setState(EdgeState::visited);
                getVertex(neighborID)->setState(VertexState::visited);

                isDeadEnd = false;
            }
        }

        // Mark dead end if no unvisited neighbors found
        if (isDeadEnd){
            getVertex(current)->setState(VertexState::deadend);
        }
    }

    // Mark the remaining vertices in the queue as dead ends
    while (!openSet.empty()){
        getVertex(openSet.top().first)->setState(VertexState::deadend);
        openSet.pop();
    }

    // Reconstruct the path from end to start
    astar_path = reconstructShortestPath(start, end, parent);

    // End time measurement
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> astar_duration = end_time - start_time;

    // Return the path if connected
    if (!astar_path.empty() && astar_path.front() == getVertex(start)){
        printShortestPath(astar_path, visited_count, astar_duration, "A*");
    } else {
        qInfo() << "No connection between start and end vertices";
    }
}


void Graph::A_star_IPQ(uint32_t start, uint32_t end){
    /* Perform the A* algorithm on the weighted graph using an Indexed Priority Queue and a heuristic function (Haversine Formula) and print the result in the console
     * We used the Haversine formula since it uses the latitude and longitude of the vertices and is therefore invariant to the mercator projection
     *
     * @param uint32_t start, uint32_t end
     */

    // Start time measurement
    auto start_time = chrono::high_resolution_clock::now();

    // Free the memory so that the old path is overridden
    astar_path.clear();

    int visited_count = 0; // Track the number of visited vertices

    // Set (log(N) complexity) for visited vertices
    std::set<uint32_t> closed_set;

    // Define and populate the maps
    unordered_map<uint32_t, double> gScore;
    unordered_map<uint32_t, double> fScore;
    unordered_map<uint32_t, uint32_t> parent; // Parent map to record the best path (Key: neighbor vertex ; Value: current vertex) O(1) complexity

    for (const auto& elem: vertices_map){
        gScore[elem.first] = numeric_limits<double>::infinity();
        fScore[elem.first] = numeric_limits<double>::infinity();
        parent[elem.first] = numeric_limits<uint32_t>::infinity();
    }

    gScore[start] = 0; // The start node has a g cost of 0
    fScore[start] = heuristic(start,end); // The start node has a f cost of the heuristic from start to end (h = f + g but g = 0 in this case)

    // Define the Indexed Priority Queue for A*
    Ipq openSet(vertices_map.size()); // Create the Index Priority Queue object
    openSet.insert(start, fScore[start]); // Add the start vertex

    // A* loop
    while (!openSet.isEmpty()){
        uint32_t current = openSet.popMin(); // Get the next most promising vertex based on cost

        if (current == end) break; // If the end vertex was found, we stop

        if (closed_set.find(current) != closed_set.end()) continue; // Continue if the current vertex has already been visited
        closed_set.insert(current); // Add the current vertex to the visited ones
        ++visited_count;

        bool isDeadEnd = true;

        // Explore the neighbors of the current vertex
        for (const auto& neighbor: getVertex(current)->getNeighbors()){
            uint32_t neighborID = neighbor.first->getID();

            // Skip already visited neighbors
            if (closed_set.find(neighborID) != closed_set.end()) continue;

            // Get the edge from the current vertex to the neighbor and compute the tentative g score
            string id = to_string(getVertex(current)->getID()) + "." + to_string(neighbor.first->getID());
            auto tentative_gScore = gScore[current] + getEdge(id)->getLength();

            if (tentative_gScore < gScore[neighborID]){ // If the score is less than the current one saved for the neighbor, update everything accordingly
                parent[neighborID] = current; // New shortest node found, add to saved path
                gScore[neighborID] = tentative_gScore;
                fScore[neighborID] = tentative_gScore + heuristic(neighborID, end);

                // Check if the neighbor is already in the IPQ and treat the corresponding case
                if (openSet.contains(neighborID)){
                    openSet.decreaseKey(neighborID, fScore[neighborID]);
                }
                else {
                    openSet.insert(neighborID, fScore[neighborID]);
                }

                // Set edge and vertex status
                getEdge(id)->setState(EdgeState::visited);
                getVertex(neighborID)->setState(VertexState::visited);

                isDeadEnd = false;
            }
        }

        // Mark dead end if no unvisited neighbors found
        if (isDeadEnd){
            getVertex(current)->setState(VertexState::deadend);
        }
    }

    // Mark the remaining vertices in the queue as dead ends
    while (!openSet.isEmpty()){
        getVertex(openSet.popMin())->setState(VertexState::deadend);
    }

    // Reconstruct the path from end to start
    astar_path = reconstructShortestPath(start, end, parent);

    // End time measurement
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> astar_duration = end_time - start_time;

    // Return the path if connected
    if (!astar_path.empty() && astar_path.front() == getVertex(start)){
        printShortestPath(astar_path, visited_count, astar_duration, "A*");
    } else {
        qInfo() << "No connection between start and end vertices";
    }
}

vector<Vertex*> Graph::getAStarPath(){
    /* Retrieve computed A* shortest path
     *
     * @return vector<Vertex*> astar_path
     */
    return astar_path;
}

//--------------------------------------- Path reconstruction ---------------------------------------//
vector<Vertex*> Graph::reconstructShortestPath(uint32_t start, uint32_t end, unordered_map<uint32_t, uint32_t> parent){
    /* Reconstructs the shortest path computed by the chosen algorithm
     *
     * @param uint32_t start, uint32_t end, unordered_map<uint32_t, uint32_t> parent
     * @return vector<Vertex*> reconstructed_path from start to finish
     */

    // Container for reconstructed path
    vector<Vertex*> reconstructed_path;

    // Reconstruct the path from end to start
    Vertex* prevVertex = nullptr;
    for (uint32_t at = end; at != numeric_limits<uint32_t>::infinity(); at = parent[at]){
        if (prevVertex != nullptr){
            string id = to_string(getVertex(at)->getID()) + "." + to_string(prevVertex->getID());
            getEdge(id)->setState(EdgeState::mainpath);
            getVertex(at)->setState(VertexState::mainpath);
        }
        prevVertex = getVertex(at);
        reconstructed_path.push_back(getVertex(at));
    }

    // Reverse the path from start to end
    reverse(reconstructed_path.begin(), reconstructed_path.end());

    // Set states of start and end vertices
    reconstructed_path.front()->setState(VertexState::start);
    reconstructed_path.back()->setState(VertexState::end);

    return reconstructed_path;
}


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
             << ", length = " << setw(10) << fixed << setprecision(2) << length
             << ", (x, y) = (" << setw(10) << element->x << ", " << setw(10) << element->y << ")" << endl;

        cnt++;
        prevVertex = element; // Save previous vertex
    }

    cout << "Path total length: " << length << " m" << endl;
    cout << "INFO: path calculated in " << Commify(duration.count()) << "us" << endl;
}












// void Graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
//     QGraphicsItem::mousePressEvent(event);
//     update();
// }

// void Graph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
// {
//     if (event->modifiers() & Qt::ShiftModifier) {
//         stuff << event->pos();
//         update();
//         return;
//     }
//     QGraphicsItem::mouseMoveEvent(event);
// }

// void Graph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// {
//     QGraphicsItem::mouseReleaseEvent(event);
//     update();
// }


