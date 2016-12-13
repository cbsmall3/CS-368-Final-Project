//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_GRAPH_H
#define REALGRAPH_GRAPH_H
#include "Edge.h"
#include "Vertex.h"
#include "VertexHash.h"
#include "VertexEqual.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <utility>
#include <algorithm>

typedef unordered_map <Vertex,std::vector<Edge>,VertexHash,VertexEqual> Map; 

class Graph {
public:

    Graph();	
    Graph(const std::vector<Vertex> v);
    void printGraph();
    Map getGraph() const;
    void insert(const Vertex &v);
    void remove(const Vertex &v); 
    void setGraph(const Map &other);  

private:
    
     Map graph;
     static constexpr double PI = 3.141592653589793;
     static constexpr double EARTH_RADIUS = 6371000; //In meters
     Map makeGraph(std::vector<Vertex> input);
     double findMinDist(double latStart, double longStart, double latEnd, double longEnd);

    
};




#endif //REALGRAPH_GRAPH_H
