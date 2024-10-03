/*
* Project: A_star algorithm 
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Graph.cpp file 
* Contains method definition for the Graph class
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <utility>
#include <unordered_map>


#include "Graph.h"
#include "Vertex.h"


using std::string;
using std::vector;
using std::stoi;
using std::stof;
using std::stod;
using std::unordered_map;


Graph::Graph(string graph_data_file) {
    // Read file and store it in a map
    string file_name{graph_data_file};

    std::ifstream file(file_name, std::ios::in);
    // Check if file is open
    if (!file.is_open()){
        std::cerr << "Error: Could not open the map file !" << std::endl;
    }

    string line;
    // Read the every line of the file
    while (std::getline(file, line)){
        std::stringstream ss(line);
        string value;
        vector<string> row;

        // Split line by commas and save in vector
        while (std::getline(ss, value, ',')){
            row.push_back(value);
        }

        if (row[0] == "V"){ //V,vertexid,longitude,latitude,x*,y*
            // Create vertex object with arguments: latitude (float) / longitude (float) / id (uint32_t) / x (int) / y (int)
            if (row.size() == 6){ // We have values for x and y
                Vertex v = new Vertex(stof(row[2]), stof(row[3]), static_cast<uint32_t>(stoi(row[1])), stoi(row[4]), stoi(row[5]));
            }
            else { 
                Vertex v = new Vertex(stof(row[2]), stof(row[3]), static_cast<uint32_t>(stoi(row[1])));
            }
            
            // Store created vertex
            vertices_map.insert({static_cast<uint32_t>(stoi(row[1])), v}); 
        }

        else if (row[0] == "E"){ 
            // Create edge object with arguments and store it: source id (int) / destination id (int) / length (double) / name (string)
            Edge e = new Edge(stoi(row[1]), stoi(row[2]), stod(row[3]), row[4]);
            edges_map.insert({, e});
        }

        else if (row[0] == "#"){ // Comment has been detected -> skip
        }

    }

    file.close();    
}