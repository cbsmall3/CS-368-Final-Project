//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_EDGE_H
#define REALGRAPH_EDGE_H
#include "Edge.h"
#include "Vertex.h"
#include <string>
#include <sstream>


using namespace std;


class Vertex;

class Edge {
    public:
	
	Edge();

	//Constructor
	Edge(Vertex &org, Vertex &dest, double dist);
        
        //Gettors
        Vertex& getOrigin();
        Vertex& getDestination();
        double getDistance();

        

        
     private:
        
	//Reference variables
	Vertex origin;
        Vertex destination;
	double distance;


     };


#endif //REALGRAPH_EDGE_H
