#include <iostream>
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include <fstream>
#include <string>


int main() {
    Vertex v1 = Vertex("Madison");
    Vertex *p1 = &v1;
    Vertex v2 = Vertex("Kenosha");
    Vertex *p2 = &v2;
    Vertex v3 = Vertex("NYC");
    Vertex *p3 = &v3;

    //At Madison, adding edge to other cities with given long and lat
    v1.addEdge(p2, 100, 100);
    v1.addEdge(p3, 1600, 1600);

    //Distance from Kenosha to Madison and NYC
    v2.addEdge(p1, 150, 150);
    v2.addEdge(p3, 1450, 1450);

    //Distance from NYC to Madison and Kenosha
    v3.addEdge(p1, 1600, 1600);
    v3.addEdge(p2, 1450, 1450);

    Graph g;

    //populate the graph
    g.Graph::insert(p1);
    g.Graph::insert(p2);
    g.Graph::insert(p3);

    g.printGraph();
    return 1;
}

//
//    //input file format:: "city name,longitude,latitude"
//
//    std::ifstream inputFile;
//    std::string inputFileName;
//    while((!inputFile.is_open())) {
//        std::cout << "What is the input file called?" << std::endl;
//        getline(std::cin, inputFileName);
//        inputFile.open(inputFileName.c_str());
//    }
//
//    std::string line;
//    while(getline(inputFile, line)) {
//        //extracts city name
//        std::string cityName;
//        getline(inputFile, cityName, ',');
//
//        //extracts longitude value
//        std::string longitudeString;
//        getline(inputFile, longitudeString, ',');
//        double longitude = std::stod(longitudeString);
//
//        //extracts latitude value
//        std::string latitudeString;
//        getline(inputFile, latitudeString, ',');
//        double latitude = std::stod(latitudeString);
//
//        //create a graph node with this information
//
//    }