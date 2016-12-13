//
// Created by Charles Grosz on 11/6/16.
//
#include "Edge.h"
#include "Vertex.h"
#include <cmath>



using namespace std;

//class Vertex;

Vertex orig,dest;


Edge::Edge() : origin(orig), destination(dest), distance(findMinDist(origin.getLatitude(),origin.getLatitude(),destination.getLatitude(),destination.getLongitude())) {}

Edge::Edge(Vertex &orig, Vertex &dest, double dist)  {

	origin=orig;
	destination=dest;
	distance=dist;

} 

Vertex& Edge::getOrigin() {return origin;}

Vertex& Edge::getDestination() {return destination;}

double Edge::getDistance() {return distance;}


void Edge::printEdge() {

        Vertex v1 = getOrigin();

	Vertex v2 = getDestination();

	std::cout<<"Origin: "<<std::endl;
      
        v1. printVertex();

	std::cout<<"Destination: "<<std::endl;
  
        v2.printVertex();
      
  std::cout<<"Distance between: "<<std::endl;    

	std::cout<<getDistance()<<std::endl;

		
	
}

double Edge::findMinDist(double latStart, double longStart, double latEnd, double longEnd) { //REVISED
	

	double x, y, z, a;
	

	latEnd = PI * latEnd/180;
	latStart = PI * latStart/180;
	longEnd = PI * longEnd/180;
	longStart = PI * longStart/180;
	y = pow(sin((latEnd - latStart) / 2), 2);
	z = pow(sin((longEnd - longStart) / 2), 2);
	x = y + cos(latEnd) * cos(latStart) * z;
	a = atan2(sqrt(x), sqrt(1 - x));
	return 2 * EARTH_RADIUS * a;
}

bool Edge::operator == (const Edge &other) const {

   if(origin==other.origin && destination==other.destination && distance == other.distance) {

		return true;

	}

	return false; 

}

bool Edge::operator != (const Edge &other) const {

   	if(origin==other.origin && destination==other.destination && distance == other.distance) {

		return false;

	}

	return true; 

}
