#include "VertexEqual.h"




bool VertexEqual::operator () (const Vertex& lhs, const Vertex& rhs) const
 		{
	
    			return (lhs.getName() == rhs.getName()) && (lhs.getLatitude() == rhs.getLatitude()) && (lhs.getLongitude() == rhs.getLongitude());
 		}