//
// Created by Charles Grosz on 11/6/16.
//
#include "Edge.h"
#include "Vertex.h"




using namespace std;

Vertex dest;

Vertex orig=dest;


Edge::Edge() : origin(orig), destination(dest), distance(0.0) {}

Edge::Edge(Vertex &orig, Vertex &dest, double dist)  {

	origin=orig;
	destination=dest;
	distance=dist;

} 

Vertex& Edge::getOrigin() {return origin;}

Vertex& Edge::getDestination() {return destination;}

double Edge::getDistance() {return distance;}



