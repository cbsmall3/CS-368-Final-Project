//
// Created by Charles Grosz on 11/6/16.
//
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"

Graph::Graph(std::vector<Vertex*> input) {

	int size  = input.size();
	
	if(size<1) { //error handling for empty input list

	   std::cerr <<"No cities on list. Please check your list." << std::endl;

	} else if(size < 2) { //error handling for only one item

	    Edge* edge;

	    vector<Edge*> edges;

	    edges.resize(size);

	    edge->orig=input[0];

            edge->dest=input[0];

	    edge->dist = 0.0;

	    edges.push_back(edge);
	
	    graph[input[0]]=edges;

	    return graph;

	}

	int n = size - 1; 	

	double avg, std_dev, sum_sqrd; //long values for mean, standard deviation, minimum span and sum sqaured initialized
        
	std::vector<double> dist; //vector used to hold the distances between adjacent vertices

	std::vector<Vertex*> list; //

	dist.resize(size);

        list.resize(size);
	
	for (int i = 0; i < size; i++) {

	    avg=0.0; //initialize mean to zero
	    sum_sqrd=0.0; //initialize sum squared to zero
	    dist[0]=avg;
	    std::vector<Edge*> edges; //initialize vector hold edges for map value
	    edges.resize(n);
	    copy(input.begin(), input.end(),back_inserter(list)); //copy initial list to working list

	    //sort copy list so that current Vertex is at front and list is in ascending order
  	    sort(list.begin(), list.end(), [](Vertex &v1, Vertex &v2)) {return getDistance(input[i]->latitude,input[i]->longitude,v1->latitude,v1->longitude)>getDistance(input[i]->latitude,input[i]->longitude,
               		v2->latitude,v2->longitude)});
	    
	    
	   for (int j = 1; j < size; j++) {

		dist[j]=getDistance(list[0]->latitude,list[0]->longitude,list[j]->latitude,list[j]->longitude);		
	        avg+=dist[j]/n;//accumulates mean value
	        sum_sqrd+=pow(dist[j],2); //accumulates sum of squared distances
	        
              }

	      std_dev=std::sqrt((sum_sqrd/n)-size*(std::pow(avg,2))/n); //calculates the standard deviation
	
                for (int k = 1; k < size; k++) {
	
		     if(std::abs(dist[k]-avg)<=std_dev*exp(-1*pow((k-1)/n,2))) { //if difference between mean distance and distance to that...
							 			 //...city is not greater than adjusted standard deviation...
										 //... make new edge and add new edge to main edge list... 
			Edge* edge;				 	         //...for this vertex
		        edge->orig=list[0];
			edge->dest=list[k];
			edge->dist=dist[k];
			edges.push_back(edge);
		
                     }
				     
		}

		//before finishing the outermost for-loop create new entry in map and clear working list for next entry


	graph[list[0]]=edges;
	list.clear();

	

	}

	return graph;

}


unordered_map<Vertex*, std::vector<Edge*>> getGraph {

	return graph;

}

void Graph::printGraph() {

	for(auto it = begin(); it!=end(); ++it) {

	   Vertex* v =*it->first;

           std::cout <<"City name: "<< v->getName() << std::endl;

           std::cout << "Neigbors: ";

	   std::vector<Edge*> edges=it->second;

	   for(auto itr = edges.begin(); itr!=edges.end(); ++itr) {

		Vector* x = *itr;

		std::cout<<x->getName()<<", ";


            }
	
	}

    return;
}

