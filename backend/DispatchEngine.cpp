#include "DispatchEngine.h"
#include <climits>

// Add driver to system
void DispatchEngine::addDriver(Driver* d) {
    drivers.push_back(d);
}

// Find best driver for a trip using shortest path
Driver* DispatchEngine::findDriverForTrip(Trip* trip) {
    string pickupLoc = trip->getRider()->getpickup();
    
    Driver* bestDriver = nullptr;
    int minDistance = INT_MAX;

    for (auto d : drivers) {
        if (d->isAvailable()) {
            int dist = cityMap->shortestPath(d->getLocation(), pickupLoc);
            if (dist != -1 && dist < minDistance) {
                minDistance = dist;
                bestDriver = d;
            }
        }
    }

    if (bestDriver != nullptr) {
        bestDriver->setAvailable(false);
        trip->assignDriver(bestDriver);
        return bestDriver;
    }

    return nullptr;
}

