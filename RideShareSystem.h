#ifndef RIDESHARESYSTEM_H
#define RIDESHARESYSTEM_H

#include <vector>
#include "City.h"
#include "Driver.h"
#include "Rider.h"
#include "Trip.h"
#include "DispatchEngine.h"
#include "RollbackManager.h"

using namespace std;

class RideShareSystem {
private:
    City city;
    vector<Driver*> drivers;
    vector<Trip*> trips;
    DispatchEngine dispatch;
    RollbackManager rollbackMgr;

public:
    RideShareSystem(string cityName);

    void addDriver(Driver* d);
    void requestTrip(Trip* t);
    bool assignTrip(Trip* t);
    void cancelTrip(Trip* t);
    void completeTrip(Trip* t);
    void rollbackLast(int k = 1);
};

#endif
