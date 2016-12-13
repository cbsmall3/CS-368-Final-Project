//
// Created by Charles Grosz on 11/6/16.
//

#include "Vertex.h"


Vertex::Vertex():name(" "),longitude(0.0),latitude(0.0) {}

Vertex::Vertex(std::string id, double lat, double lng) {

	name=id;
	longitude=lng;
	latitude=lat;

}

//Gettors
std::string Vertex::getName() const {return name;}
double Vertex::getLatitude() const {return latitude;}

int Vertex::getLatitudeAsInt() const {
  
  int x = static_cast<int> (latitude);
  return x;
  
 }

double Vertex::getLongitude() const {return longitude;}

int Vertex::getLongitudeAsInt() const {
  
  int x = static_cast<int> (longitude);
  
  
  return x ;
  
}


    
 void Vertex::printVertex() {
   
   std::cout<<" City name: "<< getName() << "Latitude: " << getLatitude() << "Longitude: " << getLongitude() << std::endl;

 }
    

    

bool Vertex::operator == (const Vertex &other) const {

          if(name==other.name && latitude==other.latitude && longitude == other.longitude) {

		return true;

	}

	return false; 

}

bool Vertex::operator != (const Vertex &other) const {

	 if(name==other.name && latitude==other.latitude && longitude == other.longitude) {

		return false;

	}

	return true; 
}



