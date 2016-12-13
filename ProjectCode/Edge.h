//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_EDGE_H
#define REALGRAPH_EDGE_H
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"



class Edge {
    public:
        
	Edge(Vertex *org, Vertex *dest, double dist);


        Vertex* getOrigin();
        Vertex* getDestination();
        double getDistance();


    private:

        Vertex* origin;
        Vertex* destination;
        double distance;

};


#endif //REALGRAPH_EDGE_H
