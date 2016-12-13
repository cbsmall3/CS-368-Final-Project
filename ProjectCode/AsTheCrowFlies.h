#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std;

//#include <boost/algorithm/string.hpp>



///////////////////////////////////////////////////////////////////////////////

//                   ALL STUDENTS COMPLETE THESE SECTIONS
// Title:            Final Project
// Files:            AsTheCrowFlies.hpp
// Semester:         CS368 
//
// Author:           Charles B. Small III
// Email:            csmall3@wisc.edu
// CS Login:         small-iii
// Lecturer's Name:  Gerald
//
//////////////////// PAIR PROGRAMMERS COMPLETE THIS SECTION ////////////////////
//
//                   
// Pair Partner:     N/A
// Email:            N/A
// CS Login:         N/A
// Lecturer's Name:  N/A
// Lab Section:      N/A
//
//////////////////// STUDENTS WHO GET HELP FROM OTHER THAN THEIR PARTNER //////
//                   must fully acknowledge and credit those sources of help.
//                   Instructors and TAs do not have to be credited here,
//                   but tutors, roommates, relatives, strangers, etc do.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide //////////////////////////////////
/// <summary>
/// This class creates a virtual traveling suite which allows a user to plan and
/// store trips as well as manage and view available cities they would like to
/// visit
/// 
/// 
/// 
/// @author Charles Small/csmall3@wisc.edu
/// </summary>

/// <summary>
/// This is where program execution starts.
/// </summary>
/// <param name="Uses"> parameter args which is not used </param>


class AsTheCrowFlies
{

	// DATA FIELDS

private:
	
	static std::vector<Vertex> main_city_list;
        static std::vector<Vertex> user_city_list;
	static std::vector<Edge> tripList;
	static const double EARTH_RADIUS = 6371000; // in meters
	static const double PI = 3.141592653589793;


	/*
	 * The method 'processCityList' takes data from a text file and adds it to the
	 * vector 'main_city_list'
	 */

public:
	static void processCityList(const std::string &filename);

	static void addCity() throw(std::exception);

	static void writeCitiesList(const std::string &filename);

	static void createTrip() throw(std::exception);

	static std::vector<string> split(string str, const char dlm);

	static double getDistance(double latStart, double longStart, double latEnd, double longEnd);

	static std::deque <Vertex> findShortestPath();

	static void main(vector<string> &args) throw(std::exception);


};
