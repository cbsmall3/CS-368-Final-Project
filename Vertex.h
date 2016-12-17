//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_VERTEX_H
#define REALGRAPH_VERTEX_H
#include "Vertex.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

class Vertex {
public:
    
    //Default constructor for intializer list
    Vertex();
	
    //Primary Constructor
    Vertex(std::string id, double lng, double lat);
    
    //Gettors
    std::string getName() const;
    double getLongitude() const;
    double getLatitude() const ;
    int getLatitudeAsInt() const;
    int getLongitudeAsInt() const;
    bool operator == (const Vertex &v) const;
    bool operator != (const Vertex &v) const;
    
    void printVertex();//prints content of Vertex
 
private:

    //Reference variables
    std::string name;
    double longitude;
    double latitude;
    	 


    //Overloaded operators
    //friend Vertex& operator = (const Vertex &v);
    
   };


#endif //REALGRAPH_VERTEX_H
