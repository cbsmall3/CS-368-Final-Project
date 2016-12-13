//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_GRAPH_H
#define REALGRAPH_GRAPH_H
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "Vertex.h"



class Graph {
public:
    
    Graph(std::vector<Vertex*> list) {}
    void printGraph();
    uordered_map <Vertex*, std::vector <Edge*>> getGraph();

private:
    uordered_map <Vertex*, std::vector <Edge*>> graph;
};


#endif //REALGRAPH_GRAPH_H
