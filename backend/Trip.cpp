#include "Trip.h"

// Constructor
Trip::Trip(int id, Rider* r) {
    tripId = id;
    rider = r;
    driver = NULL;
    state = REQUESTED;
    distance = 0;
}

// Getters
int Trip::getTripId() const {
    return tripId;
}

Rider* Trip::getRider() const {
    return rider;
}

Driver* Trip::getDriver() const {
    return driver;
}

TripState Trip::getState() const {
    return state;
}

int Trip::getDistance() const {
    return distance;
}

// Assign driver
void Trip::assignDriver(Driver* d) {
    if (state == REQUESTED) {
        driver = d;
        state = ASSIGNED;
    }
}

// Start trip
void Trip::startTrip() {
    if (state == ASSIGNED) {
        state = ONGOING;
    }
}

// Complete trip
void Trip::completeTrip(int dist) {
    if (state == ONGOING) {
        distance = dist;
        state = COMPLETED;
    }
}

// Cancel trip
void Trip::cancelTrip() {
    if (state == REQUESTED || state == ASSIGNED) {
        state = CANCELLED;
    }
}

void Trip::setState(TripState s) {
    state = s;
}

void Trip::setDriver(Driver* d) {
    driver = d;
}
