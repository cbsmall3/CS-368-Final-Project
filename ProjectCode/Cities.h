#pragma once

#include <string>
#include <ostream>
#include <sstream>




//using namespace std;





///////////////////////////////////////////////////////////////////////////////
//                   ALL STUDENTS COMPLETE THESE SECTIONS
// Main Class File:  AsTheCrowFlies
// File:             Cities.hpp
// Semester:         CS368 Fall 2016
//
// Author:           (your name and email address)
// CS Login:         (your login name)
// Lecturer's Name:  (name of your lecturer)
// Lab Section:      (your lab section number)
//
//////////////////// PAIR PROGRAMMERS COMPLETE THIS SECTION ////////////////////
//
// Pair Partner:     N/A
// Email:            N/A
// CS Login:         N/A
// Lecturer's Name:  N/A
// Lab Section:      N/A
//
//////////////////// STUDENTS WHO GET HELP FROM OTHER THAN THEIR PARTNER //////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide //////////////////////////////////
/// <summary>
/// This class creates the data management structures which allows a user to
/// enter and view available cities they would like to visit
/// 
/// 
/// 
/// @author Charles Small/csmall3@wisc.edu
/// </summary>

/// <summary>
/// This is where program execution starts.
/// </summary>
/// <param name="This">
///            class uses no class wide paramenters </param>

class Cities
{

	// INSTANCE FIELDS//

private:
	std::string city = "";
	std::string state ="";
	double latitude = 0.0;
	double longitude = 0.0;
	
	
	
        

	// CONSTRUCTOR
public:
	Cities(const std::string &state, const std::string &city, double latEntry, double longEntry);

	// GETTERS

	virtual std::string getCityName();

	virtual std::string getStateName();

	virtual double getLongitude();

	virtual double getLatitude();

	// toString

	virtual std::string printDouble(double dbl);

	virtual std::string printCityData();

	

};
