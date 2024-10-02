#include <iostream>
#include <list>


class Graph {
    public :
        Graph(int id, int lat, int long) {
            //mercator's projection calcution
            this->x = x_mercato;
            this->y = y_mercato;
        }

        void shortest_path_BFS(Vertex start, Vertex end) ;
        void shortest_path_Dijstra(Vertex start, Vertex end);
        void shortest_path_astar(Vertex start, Vertex end);
        
    private :
        std::list<int> vertices;
        std::list<int> edges;
}
class Vertex {
    private :
        int x;
        int y;
        int id;

        //list of connected vertices to the current vertex
        std::list<int> connections; //[ [vertex1, edge1], [Vertex2,edge2] ]
}

class Edge {
    private :
        Vertex origin;
        Vertex destination;
        double length;
        char name;
        double id = origin_id*1000000+destination_id
}