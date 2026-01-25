#include "RideShareSystem.h"
#include <iostream>

RideShareSystem::RideShareSystem() : dispatch(&city) {}

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
            d->decrementTrips();
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

// Analytics
double RideShareSystem::getAvgTripDistance() {
    if (trips.empty()) return 0.0;
    long totalDist = 0;
    int count = 0;
    for (auto t : trips) {
        if (t->getState() == TripState::COMPLETED) {
            totalDist += t->getDistance(); // Ensure Trip has stored distance
            count++;
        }
    }
    return count > 0 ? (double)totalDist / count : 0.0;
}

void RideShareSystem::showDriverUtilization() {
    cout << "\n--- Driver Utilization ---\n";
    for (auto d : drivers) {
        cout << "Driver " << d->getName() << ": " << d->getCompletedTrips() << " trips\n";
    }
}

void RideShareSystem::showTripStatus() {
    int req = 0, ass = 0, ong = 0, comp = 0, canc = 0;
    for (auto t : trips) {
        switch (t->getState()) {
            case REQUESTED: req++; break;
            case ASSIGNED: ass++; break;
            case ONGOING: ong++; break;
            case COMPLETED: comp++; break;
            case CANCELLED: canc++; break;
        }
    }
    cout << "\n--- Trip Status Report ---\n";
    cout << "Requested: " << req << endl;
    cout << "Assigned: " << ass << endl;
    cout << "Ongoing: " << ong << endl;
    cout << "Completed: " << comp << endl;
    cout << "Cancelled: " << canc << endl;
}
