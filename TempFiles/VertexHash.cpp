
#include "VertexHash.h"



 		std::size_t VertexHash::operator()(const Vertex &k) const {
     			return std::hash<std::string>()(k.getName())^std::hash<int>()(k.getLongitudeAsInt())^std::hash<int>()(k.getLatitudeAsInt() << 1);
 		}
		
		

      
