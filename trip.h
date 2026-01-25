#ifndef TRIP_H
#define TRIP_H

#include "Rider.h"
#include "Driver.h"

// Trip states
enum TripState {
    REQUESTED,
    ASSIGNED,
    ONGOING,
    COMPLETED,
    CANCELLED
};

class Trip {
private:
    int tripId;
    Rider* rider;
    Driver* driver;
    TripState state;
    int distance;

public:
    // Constructor
    Trip(int id, Rider* r);

    // Getters
    int getTripId() const;
    Rider* getRider() const;
    Driver* getDriver() const;
    TripState getState() const;
    int getDistance() const;

    // Setters / state change
    void assignDriver(Driver* d);
    void startTrip();
    void completeTrip(int dist);
    void cancelTrip();
};

#endif
