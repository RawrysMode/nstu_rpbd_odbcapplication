#ifndef ROUTE_H
#define ROUTE_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include "ActiveRecord.h"
#include "City.h"

using namespace std;

class Route : public ActiveRecord {

private:
	int insert(HDBC hDBC) override;
	bool update(HDBC hDBC) override;

public:
	int routeCost;
	int departureCityId;
	int destinationCityId;
	City departureCity;
	City destinationCity;
	string departureCityS, destinationCityS;

	Route();
	Route(int id);
	Route(int id, string departureCity, string destinationCity, int routeCost);


	bool remove(HDBC hDBC) override;
	void setDepartureCity(City departureCity);
	void setDestinationCity(City destinationCity);
	Route load(HDBC hDBC);

	friend bool operator==(const Route& lhs, const Route& rhs) {
		return lhs.id == rhs.id && lhs.departureCityId == rhs.departureCityId && lhs.destinationCityId == rhs.destinationCityId;
	}

	std::string toString() {
		char s[512];
		sprintf_s(s, 512, "Route cost: %d, departure city: %s, destination city: %s", routeCost, departureCity.toString().c_str(), destinationCity.toString().c_str());
		return string(s);
	}
	
	std::string toString2() {
		char s[512];
		sprintf_s(s, 512, "Route cost: %d, departure city: %s, destination city: %s", routeCost, departureCityS.c_str(), destinationCityS.c_str());
		return string(s);
	}
};

#endif
