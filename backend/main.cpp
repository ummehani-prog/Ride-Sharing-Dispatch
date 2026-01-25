#include <iostream>
#include <vector>

#include "Driver.h"
#include "Rider.h"
#include "Trip.h"
#include "DispatchEngine.h"
#include "RideShareSystem.h"
#include "City.h"

using namespace std;

int main(int argc, char* argv[]) {
    // CLI Mode: ./dispatch_system solve <Pickup> <D1Name> <D1Loc> ...
    if (argc > 1 && string(argv[1]) == "solve") {
         City myCity;
        // Add sample locations (Zones) for CLI context (or pass fully via args)
        // For simplicity, we reproduce the basic map or rely on hardcoded map for the demo
        myCity.addLocation("Downtown");
        myCity.addLocation("Uptown");
        myCity.addLocation("Suburbs");
        myCity.addLocation("Airport");
        myCity.addLocation("EastSide");

        // Add roads (Distances)
        myCity.addRoad("Downtown", "Uptown", 5);
        myCity.addRoad("Uptown", "Suburbs", 10);
        myCity.addRoad("Downtown", "Suburbs", 12);
        myCity.addRoad("Uptown", "Airport", 15);
        myCity.addRoad("Suburbs", "EastSide", 8);
        myCity.addRoad("Downtown", "EastSide", 20);
        
        DispatchEngine engine(&myCity);

        if (argc < 3) {
            cout << "Error: Missing pickup location\n";
            return 1;
        }
        string pickup = argv[2];
        
        // Parse drivers from args
        for (int i = 3; i < argc; i += 2) {
            if (i + 1 < argc) {
                string dName = argv[i];
                string dLoc = argv[i+1];
                engine.addDriver(new Driver(i, dName, dLoc, "Zone"));
            }
        }

        Trip t(1, new Rider(1, "User", pickup, "Dest"));
        Driver* d = engine.findDriverForTrip(&t);
        
        if (d) {
             // Calculate distance strictly for output
             int dist = myCity.shortestPath(d->getLocation(), pickup);
             cout << "Selected: " << d->getName() << " | Location: " << d->getLocation() << " | Distance: " << dist << endl;
        } else {
             cout << "None" << endl;
        }
        return 0;
    }

    cout << "====== RIDE SHARING DISPATCH SYSTEM - TEST SUITE ======\n";

    RideShareSystem rideApp;
    City* city = rideApp.getCity();

    // 1. Setup City Graph
    city->addRoad("A", "B", 5);
    city->addRoad("B", "C", 10);
    city->addRoad("A", "C", 20); // Longer path
    city->addRoad("C", "D", 5);
    
    // TEST 1: Shortest Path Correctness
    cout << "\nTest 1: Shortest Path Correctness (A->C)\n";
    int dist = city->shortestPath("A", "C"); // Should be 15 via B
    if (dist == 15) cout << "[PASS] Shortest Path A->C is 15\n";
    else cout << "[FAIL] Shortest Path A->C is " << dist << " (Expected 15)\n";

    // Setup Drivers
    Driver* d1 = new Driver(1, "D1", "A", "Zone1");
    Driver* d2 = new Driver(2, "D2", "B", "Zone1");
    Driver* d3 = new Driver(3, "D3", "D", "Zone2");
    rideApp.addDriver(d1);
    rideApp.addDriver(d2);
    rideApp.addDriver(d3);

    // TEST 2: Simple Trip Request
    cout << "\nTest 2: Simple Trip Request\n";
    Rider* r1 = new Rider(1, "R1", "A", "C");
    Trip* t1 = new Trip(1, r1);
    rideApp.requestTrip(t1);
    if (t1->getState() == REQUESTED) cout << "[PASS] Trip 1 Requested\n";
    else cout << "[FAIL] Trip 1 State: " << t1->getState() << endl;

    // TEST 3: Driver Assignment (Nearest)
    cout << "\nTest 3: Driver Assignment (Nearest)\n";
    // Rider at A. D1 is at A (dist 0). D2 at B (dist 5).
    bool assigned = rideApp.assignTrip(t1);
    if (assigned && t1->getDriver()->getName() == "D1") 
        cout << "[PASS] Driver D1 assigned (Distance 0)\n";
    else 
        cout << "[FAIL] Assigned: " << (assigned ? t1->getDriver()->getName() : "None") << endl;

    // TEST 4: Driver Availability Update
    cout << "\nTest 4: Driver Availability Update\n";
    if (!d1->isAvailable()) cout << "[PASS] D1 is now unavailable\n";
    else cout << "[FAIL] D1 is still available\n";

    // TEST 5: Trip Cancellation & Rollback
    cout << "\nTest 5: Trip Cancellation & Rollback\n";
    rideApp.cancelTrip(t1);
    if (t1->getState() == CANCELLED && d1->isAvailable()) 
        cout << "[PASS] Trip Cancelled, D1 available again\n";
    else 
        cout << "[FAIL] State: " << t1->getState() << ", D1 Avail: " << d1->isAvailable() << endl;

    // TEST 6: Rollback Cancellation (Undo Cancel)
    cout << "\nTest 6: Rollback Cancellation (Undo Cancel)\n";
    rideApp.rollbackLast();
    if (t1->getState() == ASSIGNED && !d1->isAvailable()) 
        cout << "[PASS] Cancel Undone. State: ASSIGNED, D1 Unavailable\n";
    else 
        cout << "[FAIL] State: " << t1->getState() << endl;
    
    // TEST 7: Complete Trip
    cout << "\nTest 7: Complete Trip\n";
    rideApp.completeTrip(t1);
    if (t1->getState() == COMPLETED && d1->getCompletedTrips() == 1) 
        cout << "[PASS] Trip Completed, Driver trip count: 1\n";
    else 
        cout << "[FAIL] State: " << t1->getState() << endl;

    // TEST 8: Rollback Completion (Undo Complete)
    cout << "\nTest 8: Rollback Completion\n";
    rideApp.rollbackLast();
    if (t1->getState() == ASSIGNED && d1->isAvailable() == false && d1->getCompletedTrips() == 0)
         cout << "[PASS] Completion Undone. D1 trips: 0\n";
    else 
         cout << "[FAIL] State: " << t1->getState() << ", D1 Trips: " << d1->getCompletedTrips() << endl;

    // TEST 9: Cross-Zone Assignment
    cout << "\nTest 9: Cross-Zone / Distance Assignment\n";
    // Rider at D. Only D3 is at D. 
    Rider* r2 = new Rider(2, "R2", "D", "A");
    Trip* t2 = new Trip(2, r2);
    rideApp.requestTrip(t2);
    rideApp.assignTrip(t2);
    if (t2->getDriver() == d3) 
        cout << "[PASS] D3 (Zone 2) assigned to Rider at D\n";
    else 
        cout << "[FAIL] Assigned: " << (t2->getDriver() ? t2->getDriver()->getName() : "None") << endl;

    // TEST 10: Invalid State Transition
    cout << "\nTest 10: Invalid State Transition\n";
    // Try to complete a REQUESTED trip (t3)
    Trip* t3 = new Trip(3, new Rider(3, "R3", "A", "B"));
    rideApp.requestTrip(t3);
    rideApp.completeTrip(t3); // Should fail print error
    if (t3->getState() == REQUESTED) 
        cout << "[PASS] Trip 3 still REQUESTED (Invalid Complete Ignored)\n";
    else 
        cout << "[FAIL] Trip 3 State: " << t3->getState() << endl;

    // Analytics Check
    cout << "\n--- Analytics Check ---\n";
    rideApp.showDriverUtilization();
    rideApp.showTripStatus(); // t1 assigned, t2 assigned, t3 requested

    return 0;
}

