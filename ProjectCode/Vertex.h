//
// Created by Charles Grosz on 11/6/16.
//

#ifndef REALGRAPH_VERTEX_H
#define REALGRAPH_VERTEX_H
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include <vector>
#include <iostream>
#include <string>



class Vertex {

public:
   
 Vertex(std::string id,double lng, double lat)) {
        
    }

    std::string getName();
    double getLat();
    double getLong();
    

private:
    
    std:string name;
    double latitude;
    double longitude;


};


#endif //REALGRAPH_VERTEX_H
