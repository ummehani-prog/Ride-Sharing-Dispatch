#include "DispatchEngine.h"

// Add driver to system
void DispatchEngine::addDriver(Driver* d) {
    drivers.push_back(d);
}

// Find best driver for a trip
Driver* DispatchEngine::findDriverForTrip(Trip* trip) {

    string pickupCity = trip->getRider()->getpickup();

    // 1️⃣ Same-zone driver
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers[i]->isAvailable() &&
            drivers[i]->getLocation() == pickupCity) {

            drivers[i]->setAvailable(false);
            trip->assignDriver(drivers[i]);
            return drivers[i];
        }
    }

    // 2️⃣ Cross-zone driver (costly)
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers[i]->isAvailable()) {

            drivers[i]->setAvailable(false);
            trip->assignDriver(drivers[i]);
            return drivers[i];
        }
    }

    // No driver found
    return NULL;
}
