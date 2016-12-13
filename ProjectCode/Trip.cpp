#include "Trip.h"

int Trip::findMinDist(double latEnd, double latStart, double longEnd, double longStart)
{
	double x = 0;
	double y = 0;
	double z = 0;
	double a = 0;
	const double pi=2*std::acos(0.0);
	latEnd = pi*latEnd/180;
	latStart = pi*latStart/180;
	longEnd = pi*longEnd/180;
	longStart = pi*longStart/180;
	y = std::pow(std::sin((latEnd - latStart) / 2), 2);
	z = std::pow(std::sin((longEnd - longStart) / 2), 2);
	x = y + std::cos(latEnd) * std::cos(latStart) * z;
	a = std::atan2(std::sqrt(x), std::sqrt(1 - x));
	int distanceBetweenCities = static_cast<int>(2 * EARTH_RADIUS * a);
	return distanceBetweenCities;

}

Trip::Trip(const std::wstring &startingCity, const std::wstring &endingCity, double latEnd, double latStart, double longEnd, double longStart)
{

	/*this->startingCity = startingCity;
	this->endingCity = endingCity;
	this->minDist = static_cast<int>(findMinDist(latEnd, latStart, longEnd, longStart));*/

}

std::wstring Trip::getStartCity()
{
	/*return startingCity;*/
}

std::wstring Trip::getEndCity()
{
	/*return endingCity;*/
}

int Trip::getMinDist()
{
	/*return minDist;*/
}

std::wstring Trip::printTripData()
{

	/*return getStartCity() + std::wstring(L" to ") + getEndCity() + std::wstring(L" as the crow flies is ") + std::wstring(L"about ") + getMinDist() + std::wstring(L" meters (~") + getMinDist() * 31 / 50000 + std::wstring(L" miles)");*/

}
