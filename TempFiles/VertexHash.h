//
// Created by Charles Small on 12/6/16.
//

#ifndef VERTEX_HASH_H
#define VERTEX_HASH_H
#include "Vertex.h"
#include <string>


using namespace std;




class VertexHash {
public:

	size_t operator() (const Vertex &v) const;
};




#endif //VERTEX_HASH_H
