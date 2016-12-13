#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <set>
#include <unordered_map>
#include <deque>
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "VertexHash.h"
#include "VertexEqual.h"

using namespace std;

        typedef pair<double, Vertex> PQI; //mapping pair for ordered set used as priority queue

	struct PQI_Comp {

		bool operator()(const PQI& lhs, const PQI& rhs) const
 		{
			
    			return lhs.first > rhs.first; 
 		}

	};

class AsTheCrowFlies {

private:
	
	//Private data members for this class
	std::vector<Vertex> main_city_list;
        std::vector<Vertex> user_city_list;
	Graph mainGraph;
	std::vector<Edge> tripList;
        static constexpr double PI = 3.141592653589793;
        static constexpr double EARTH_RADIUS = 6371000; //In meters
        
	//Private methods for this class

	//processes city data from text file and loads it to main_city_list
	std::vector<Vertex> processCityData(const std::string &filename) throw(std::exception); 
	
	//adds a new city to the main_city_list
	void addCity() throw(std::exception); 

	//checks if string entry for latitude and longitude will work
	bool is_double(const std::string& s);

        //checks if string entry for latitude and longitude will work
        bool is_int(const std::string& s);
	
	//The method 'writeCitiesList' writes the list of cities from the cityList
	//array list to a text file 
        
	void writeCitiesList(const std::string &filename) throw(std::exception);

	//The method 'createTrip creates, stores and displays the legs of a trip
	//along with a total distance traveled
	 
	void createTrip() throw(std::exception);

	//Splits a string str into tokens with char dlm as the delimitter
	std::vector<string> split(const std::string &line, const char dlm);

        //Gets list of shortest path between two vertices in a graph
	std::deque<Vertex> findShortestPath();

        //Returns Haversin min distance between two points
        double findMinDistance(double latStart, double longStart, double latEnd, double longEnd);
        
 	//Returns a list of Edges associated with that node
	std::vector<Edge> findEdges(const Vertex &v) const;
     


public:


	AsTheCrowFlies();

	//Initiates load of city list and implements the user menu
	int menu (char* filename) throw(std::exception);

};
