#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "Graph.h"

using std::string;
using std::vector;
using std::stio;

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
            Vertex v = new Vertex(std::stio(row[1]), std::stio(row[2]), static_cast<uint32_t>(std::stoi(row[3])));
        }
    }

    file.close();    
}