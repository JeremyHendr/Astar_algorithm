/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Ipq.h file
* Contains header of the Indexed Priority Queue class
*/

#ifndef IPQ_H
#define IPQ_H

#include <vector>
#include <cstdint>
#include <unordered_map>

using namespace std;

class Ipq {
    public:
        Ipq(int max_size);
        bool contains(uint32_t v); // Checks if the vertex is in the queue
        bool isEmpty(); // Checks if the queue is empty
        void insert(uint32_t v, double d); // Inserts a vertex with its distance
        void decreaseKey(uint32_t v, double d); // Decreases the key (distance) of a vertex
        uint32_t popMin(); // Pops the vertex with the minimum distance
        double getDist(uint32_t v) const; // Returns the distance of the vertex

    private:
        vector<int> heap; // Stores vertex IDs
        unordered_map<uint32_t, int> index; // Maps vertex ID to its position in the heap
        unordered_map<uint32_t, double> dist; // Stores the distance of each vertex relative to the start vertex
        int size;

        void swap(int i, int j); // Swap two nodes in the heap and updates the index array
        void swim(int i); // Move a node up the heap to that it satisfies the heap invariant to get stability
        void sink(int i); // Move a node down the heap to that it satisfies the heap invariant to get stability

};

#endif // IPQ_H
