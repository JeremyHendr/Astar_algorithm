/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Ipq.cpp file
* Contains source of the Indexed Priority Queue class
*/


#include "Ipq.h"
#include <algorithm>
#include <unordered_map>

Ipq::Ipq(int max_size)
    : heap(), size(0){
    heap.reserve(max_size);
}

bool Ipq::contains(uint32_t v){
    /* Checks if the vertex is in the queue
     *
     * @param uint32_t v (vertex id)
     * @return bool if vertex is present or not
     */
    return index.find(v) != index.end();
}

bool Ipq::isEmpty(){
    /* Checks if the queue is empty
     *
     * @return bool if empty or not
     */
    return size == 0;
}

void Ipq::insert(uint32_t v, double d){
    /* Inserts a vertex with its distance
     *
     * @param uint32_t v (vertex id), double d (length)
     */
    heap.push_back(v);
    index[v] = size;
    dist[v] = d;
    swim(size); // After the element has been added to the heap, move it to satisfy the heap invariant
    size++;
}

void Ipq::decreaseKey(uint32_t v, double d){
    /* Decreases the key (distance) of a vertex
     *
     * @param uint32_t v (vertex id), double d (length i.e. distance)
     */
    dist[v] = d; // Set the new distance
    swim(index[v]); // Reposition the node in the heap to satisfy the heap invariant (min-heap)
}

uint32_t Ipq::popMin(){
    /* Pops the vertex with the minimum distance
     *
     * @return id of vertex at the top of the heap i.e. with the smallest distance
     */

    // Update the heap, index map, position map by removing the vertex with the min distance i.e. the top of the heap in the min-heap
    int minVertex = heap[0];
    size--;
    heap[0] = heap[size];
    index[heap[0]] = 0;
    index.erase(minVertex);
    dist.erase(minVertex);
    heap.pop_back();
    sink(0);
    return minVertex;
}

double Ipq::getDist(uint32_t v) const {
    /* Returns the distance of the vertex
     *
     * @param uint32_t v (vertex id)
     * @return double (distance of vertex to start)
     */
    return dist.at(v);
}

void Ipq::swim(int i){
    /* Move a node up the heap to that it satisfies the heap invariant to get stability
     *
     * @param int i (node index to be moved)
     */

    // Move the node up the heap if its value is less than the one of the parent (min-heap)
    while (i > 0 && dist[heap[(i - 1) / 2]] > dist[heap[i]]){
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void Ipq::sink(int i){
    /* Move a node down the heap to that it satisfies the heap invariant to get stability
     *
     * @param int i (node index to be moved)
     */

    // Formula to get the children (left and right) indexes of a node in the heap: 2 * i + 1 ; 2 * i + 2
    while (2 * i + 1 < size){
        int j = 2 * i + 1;
        if (j + 1 < size && dist[heap[j + 1]] < dist[heap[j]]) j++;
        if (dist[heap[i]] <= dist[heap[j]]) break;
        swap(i, j);
        i = j;
    }
}

void Ipq::swap(int i, int j){
    /* Swap two nodes in the heap and updates the index array
     *
     * @param int i, int j : indexes of nodes to be swapped
     */
    std::swap(heap[i], heap[j]); // Swap elements in the heap
    index[heap[i]] = i; // Update index of element at i
    index[heap[j]] = j; // Update index of element at j
}
