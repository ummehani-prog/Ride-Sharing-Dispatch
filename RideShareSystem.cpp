#include "RideShareSystem.h"
#include <iostream>

RideShareSystem::RideShareSystem(string cityName) : city(cityName) {}

void RideShareSystem::addDriver(Driver* d) {
    drivers.push_back(d);
    dispatch.addDriver(d);
}

void RideShareSystem::requestTrip(Trip* t) {
    trips.push_back(t);
}

// Assign trip using DispatchEngine + rollback
bool RideShareSystem::assignTrip(Trip* t) {
    if (t->getState() != TripState::REQUESTED) {
        cout << "Invalid state for assignment\n";
        return false;
    }

    Driver* assigned = dispatch.findDriverForTrip(t);
    if (assigned) {
        auto undo = [t, assigned]() {
            t->setState(TripState::REQUESTED);
            assigned->setAvailable(true);
            t->setDriver(nullptr);
        };
        rollbackMgr.recordAction(undo);
        t->setState(TripState::ASSIGNED);
        return true;
    }

    return false;
}

// Cancel trip + rollback
void RideShareSystem::cancelTrip(Trip* t) {
    if (t->getState() == TripState::ASSIGNED || t->getState() == TripState::REQUESTED) {
        Driver* prevDriver = t->getDriver();
        auto prevState = t->getState();

        auto undo = [t, prevDriver, prevState]() {
            t->setState(prevState);
            if (prevDriver)
                prevDriver->setAvailable(false);
            t->setDriver(prevDriver);
        };
        rollbackMgr.recordAction(undo);

        if (prevDriver)
            prevDriver->setAvailable(true);

        t->setState(TripState::CANCELLED);
        t->setDriver(nullptr);
    } else {
        cout << "Trip cannot be cancelled\n";
    }
}

// Complete trip + rollback
void RideShareSystem::completeTrip(Trip* t) {
    if (t->getState() != TripState::ASSIGNED) {
        cout << "Trip cannot be completed\n";
        return;
    }

    Driver* d = t->getDriver();
    auto undo = [t, d]() {
        t->setState(TripState::ASSIGNED);
        if (d) {
            d->setAvailable(false);
            d->decrementTrips(); // agar aisa function bana lo
        }
    };
    rollbackMgr.recordAction(undo);

    t->setState(TripState::COMPLETED);
    if (d) {
        d->incrementTrips();
        d->setAvailable(true);
    }
}

// Rollback
void RideShareSystem::rollbackLast(int k) {
    rollbackMgr.rollback(k);
}
