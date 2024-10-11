# Main tasks for Astar Project
#### Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius

## Vocab
Vertex: Node aka intersection.\
Edge: Street.

## 
- [ ] Create the graph class
    - Graph class with methods to find path between two vertices
    - One graph object (1 map)
    - Contains:
        - List of all vertices
        - CHOOSE CONTAINER CORRECTLY
        - 

    
- [ ] Create function to create an unordered map with vertex and edge its connected to
- [x] Create custom hash and equal methods for vertex class so that it can be used in an unordered map
- [ ] Create a graph from the provided data file

- [ ] Code BFS
- [ ] Code Dijkstra
- [ ] Code A star
- [ ] Code visual rep in Qt

## Explanation of BFS pseudo code
```c++
Graph::bfs(uint32_t vstart) { 
 
  container<uint32_t> active_queue; 
  set<uint32_t> closed_set; 
 
  // ID of the start vertex 
  active_queue.push_end(vstart); 
 
do { 
    // from the current vertex in the front of the queue 
    // compute all vertices reachable in 1 step 
    auto vcurrent = active_queue.pop_front(); // Remove the current vertex from the queue
    closed_set.add(vcurrent);  // Add the current vertex to the explored vertices aka closed set
    for(vnext in adjacency_list of vcurrent) { // Look for the vertices reachable from the current vertex through a node (vnext = one of the adjacents of vcurrent in the list) 
      if (vnext is in closed_set) { // If vnext has already been explored we do nothing
        continue; 
      } 
      if (vnext is not already in active_queue) { // vnext hasn't been explored yet so we add it to the queue -> meaning to the list of what is still to be explored
        active_queue.push_end(vnext); 
      } 
    } 
  } while (active_queue.size() != 0) // We do this as long as the queue is not empty
}
```

- Best way is to use vector ? 
    - Random access
    - Can re-allocate memory
    - No extra pointers
    - Insertions or erase of elements NOT at the end of the vector are costly in operations
    - Overall easier access

edge gives us the source vertix id and the destination vertex id
creation of an adjacency list -> take vertex, look for edges with this vertex id as either source or destination

before algo starts, all the vertices need to be in the active queue
adjacency list = vector holds the adjacents for a vertex (vector of vector for each vertex ???)
create the adjacency list for a vertex before running the algo ??? 

loop needs to stop when end vertex has been found even if queue isnt empty


need to add to the current vertex, the vertex it can reach as well as through what edge

https://www.youtube.com/watch?v=oDqjPvD54Ss
