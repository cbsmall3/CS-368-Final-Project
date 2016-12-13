//
// Created by Charles Grosz on 11/6/16.
//
#include "Edge.h"
#include "Vertex.h"

Edge::Edge(Vertex* org, Vertex* dest, double dist){

	    origin = org;
            destination = dest;
            distance = dist;
	
}

Vertex Edge::getOrigin() {
    return origin;
}

Vertex Edge::getDestination() {
    return destination;
}

double Edge::getDistance() {
     return distance;

}

void Edge::setDistance(double new_dist) {

	this->distance=new_dist;

}


