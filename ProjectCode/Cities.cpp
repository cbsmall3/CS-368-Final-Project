#include "Cities.h"

//using namespace std;




Cities::Cities(const std::string &state, const std::string &city, double latEntry, double longEntry)
{
	this->city = city;
	this->state = state;
	this->longitude = longEntry;
	this->latitude = latEntry;
}

std::string Cities::getCityName()
{
	return city;
}

std::string Cities::getStateName()
{
	return state;
}

double Cities::getLongitude()
{
	return longitude;
}

double Cities::getLatitude()
{
	return latitude;
}

std::string printDouble(double dbl) {
  
  
  std::ostringstream strm;
  strm << dbl;
  return strm.str();
  
}



std::string Cities::printCityData()
{
	return getStateName() + "," + getCityName() + "," + printDouble(getLatitude()) + "," + printDouble(getLongitude());
}
