#ifndef DISPATCHENGINE_H
#define DISPATCHENGINE_H

#include <vector>
#include "Driver.h"
#include "Trip.h"

using namespace std;

class DispatchEngine {
private:
    vector<Driver*> drivers;

public:
    void addDriver(Driver* d);
    Driver* findDriverForTrip(Trip* trip);
};

#endif
