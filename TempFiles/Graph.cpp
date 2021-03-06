//
// Created by Charles Grosz on 11/6/16.
//
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"

using namespace std;

Map v;

//Default constructor
Graph::Graph():graph(v) {}


//Primary constructor
//@param std:vector<Vertex>


Graph::Graph(const std::vector<Vertex> v) {

	graph=makeGraph(v);

}




//Settor for map in a graph
//@param std::vector<Node> &other is new list of Graph Nodes





void Graph::setGraph(const Map &other) {
  
  graph=other;

  
} 




//Adds a new vertex to the graph
//@param const Vertex &v to be added


void Graph::insert(const Vertex &v) {

     
	//new list which will include new node plus the current list of vertices
        std::vector <Vertex> vertexList; 

	//new map with will include the new vertex
	Map new_graph;

	//New vertex added to list
	vertexList.push_back(v);
	

	//Current vertices added to end of new list
        for (auto it = graph.begin(); it!=graph.end(); ++it) {

		vertexList.push_back(it->first);

	}


	//New graph is created with new list of vertices
        new_graph=makeGraph(vertexList);

	
	graph=new_graph;

	

}



//Deletes a vertex from the graph
//@para const Vertex &v is Vertex to be deleted



void Graph::remove(const Vertex &v) {

//Remove node with first pair item of target Vertex

	bool done = false;

	for(auto it = graph.begin(); it!=graph.end() && !done; ++it) {

		if(it->first==v) {
	
		    graph.erase(it);
		    done = true;		
               
                }

	}



        //Removes all destinations with target Vertex on all edge lists

	for(auto it = graph.begin(); it!=graph.end(); ++it) {

		std::vector<Edge> edges=it->second;

	        for(auto itr = edges.begin(); itr!=edges.end(); ++itr) {

			if(itr->getDestination()==v) {
		
				edges.erase(itr);

                         }

		}

		it->second=edges;

        }

	//return; 


}






 Map Graph::getGraph() const {

	return graph;

} 






//Print contents of the graph as "Ciy Name: <city name1>
//
//"Neighbors: <neighbor1>, <neighbor2>, ...<last_neigbor>
//
//
//and so on...

 

void Graph::printGraph() {

	for(auto it = graph.begin(); it!=graph.end(); ++it) {

	   Vertex v = it->first;

           std::cout <<"City name: "<< v.getName() << std::endl;

           std::cout << "Neigbors: ";

	   std::vector<Edge> edges=it->second;

	   for(auto itr = edges.begin(); itr!=edges.end(); ++itr) {

		Vertex neighbor = itr->getDestination();

		if(itr<edges.end()-1) {

			std::cout<<neighbor.getName()<<", ";


	        } else {

			std::cout<<neighbor.getName()<<std::endl;
             
                }

		std::cout<<std::endl;

            }

           

	}		
	   
	}

    
/*Creates new vector of Graph Nodes from a vector of Vertices
*@param vector <Vertex> input provides list of vectors to make Graph
*@return vector<Node> is a graph of Nodes which are pairs of Vertices and
* a vector of Edges
*/

 Map Graph::makeGraph(std::vector<Vertex> input)

{

    

       Map new_graph;

       int size  = input.size();

       int n = size - 1;

	if(size==0) { //error handling for empty input list

	   std::cerr <<"No cities on list. Please check your list." << std::endl;

	  } else if(size==1) { //special case for only one item

	    Edge edge(input[0],input[0],0.0);

	    vector<Edge> edges;

	    edges.resize(size);

	    edges.push_back(edge);		

	    new_graph[input[0]]=edges;

	    return new_graph;

	  } else if (size == 2) { //special case for only two items

	     
	    Edge edge (input[0], input[1], findMinDist(input[0].getLatitude(),input[0].getLongitude(),
			   input[1].getLatitude(),input[1].getLongitude()));

	     vector<Edge> edges;

	     edges.resize(size);

	     edges.push_back(edge);		

	     new_graph[input[0]]=edges;

	     return new_graph;

	 }
 	
     

	double avg, std_dev, sum_sqrd; //long values for mean, standard deviation, minimum span and sum sqaured initialized
        
	std::vector<double> dist; //vector used to hold the distances between adjacent vertices

	std::vector<Vertex> list; //working list of vertices in for loops below
 
        dist.resize(size);

        list.resize(size);

	copy(input.begin(), input.end(),back_inserter(list)); //copy initial list to working list

	
	for (int i = 0; i < size; i++) {

	    avg=0.0; //initialize mean to zero
	    sum_sqrd=0.0; //initialize sum squared to zero
	    dist[0]=avg;
	    std::vector<Edge> edges; //initialize vector hold edges for map value
	    edges.resize(size);	
	   
	    
	    //sort copy list so that current Vertex is at front and list is in ascending order
  	    sort(list.begin(), list.end(), [&](const Vertex v1, const Vertex v2){return (findMinDist(input[i].getLatitude(),input[i].getLongitude(),v1.getLatitude(),v1.getLongitude())>findMinDist(input[i].getLatitude(),input[i].getLongitude(),v2.getLatitude(),v2.getLongitude()));});
	    
	   //Gets average and precursor data for standard deviation

	   for (int j = 1; j < size; j++) {

		dist[j]=findMinDist(list[0].getLatitude(),list[0].getLongitude(),list[j].getLatitude(),list[j].getLongitude());		
	        avg+=dist[j]/size;//accumulates mean value
	        sum_sqrd+=pow(dist[j],2); //accumulates sum of squared distances
	        
              }

	      std_dev=sqrt((sum_sqrd/n)-size*(pow(avg,2))/n); //calculates the standard deviation
	
                for (int k = 1; k < size; k++) {
	
		     //if the index value between the origin Vertex 
		     //...and the current Vertex is not less than 
                     //...the square root of the inverse of the... 
		     //...relative error make new edge and add new... 
                     //...edge to main edge list for this vertex	

		     if((dist[n]-dist[k]+1)/(dist[n]-dist[1]+1)>=std::sqrt(1-(std_dev/avg))) { 
			
			Edge edge (list[0], list[k], dist[k]);

	     		edges.push_back(edge);

		
                     }

		//before finishing the outermost for-loop create new entry in graph

	        new_graph[list[0]]=edges;


		}

		
        return new_graph;

	
     }
     
     	
}	

    

double Graph::findMinDist(double latStart, double longStart, double latEnd, double longEnd) { //REVISED
	

	double x, y, z, a;
	

	latEnd = PI * latEnd/180;
	latStart = PI * latStart/180;
	longEnd = PI * longEnd/180;
	longStart = PI * longStart/180;
	y = pow(sin((latEnd - latStart) / 2), 2);
	z = pow(sin((longEnd - longStart) / 2), 2);
	x = y + cos(latEnd) * cos(latStart) * z;
	a = atan2(sqrt(x), sqrt(1 - x));
	return 2 * EARTH_RADIUS * a;
}



 


