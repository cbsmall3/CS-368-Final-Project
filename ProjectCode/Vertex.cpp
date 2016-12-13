//
// Created by Charles Grosz on 11/6/16.
//

#include "Vertex.h"


Vertex::Vertex(string id, double lng, double lat) {

	name=id;
	longitude=lng;
	latitude=lat;

}

    string Vertex::getName() {return name;}
    double Vertex::getLat() {return latitude;}
    double Vertex::getLong() {return longitude;}
    

    
}


