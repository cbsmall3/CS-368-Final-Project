//
// Created by Charles Small on 12/6/16.
//

#ifndef VERTEX_EQUAL_H
#define VERTEX_EQUAL_H
#include "Vertex.h"
#include <string>


using namespace std;




class VertexEqual {
public:

	bool operator () (const Vertex& lhs, const Vertex& rhs) const;
 		
};




#endif //VERTEX_EQUAL_H