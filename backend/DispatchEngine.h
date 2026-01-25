#ifndef DISPATCHENGINE_H
#define DISPATCHENGINE_H

#include <vector>
#include "Driver.h"
#include "Trip.h"

using namespace std;

#include "City.h"

class DispatchEngine {
private:
    vector<Driver*> drivers;
    City* cityMap;

public:
    DispatchEngine(City* city) : cityMap(city) {}
    void addDriver(Driver* d);
    Driver* findDriverForTrip(Trip* trip);
};


#endif
