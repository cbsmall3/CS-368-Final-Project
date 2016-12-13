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
	bool operator == (const Edge &other) const;
	bool operator != (const Edge &other) const;
        
	void printEdge(); //Prints out content of edge
        
     private:
        
	//Reference variables
	Vertex origin;
        Vertex destination;
	double distance;
	double findMinDist(double latStart, double longStart, double latEnd, double longEnd);
        static constexpr double PI = 3.141592653589793;
        static constexpr double EARTH_RADIUS = 6371000; //In meters


	//Settors
	//void setOrigin(const Vertex &v);
	//void setDestination(const Vertex &v);
	//void setDistance(const double dist);


        //Overloaded operators
	//friend Edge& operator = (const Edge &other);
	

};


#endif //REALGRAPH_EDGE_H
