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

        if (row[0] == "V"){
            // Create vertex object with arguments: latitude (float) / longitude (float) / id (uint32_t)
            Vertex v = new Vertex(stof(row[1]), stof(row[2]), static_cast<uint32_t>(stoi(row[3])));
        }
        else if (row[0] == "E"){ //# E,source_vid,dest_vid,length,name,extra0,extra1
            // Create edge object with arguments: source id () / destination id () / length () / name ()
            //Edge e = new Edge();
        }
    }

    file.close();    
}