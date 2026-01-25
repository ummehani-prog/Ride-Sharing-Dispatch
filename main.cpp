#include <iostream>
#include <vector>

#include "driver.h"
#include "rider.h"
#include "trip.h"
#include "DispatchEngine.h"

using namespace std;

int main() {

    DispatchEngine engine;

    vector<Driver*> drivers;
    vector<Rider*> riders;
    vector<Trip*> trips;

    int choice = 0;
    int driverId = 0, riderId = 0, tripId = 0;

    do {
        cout << "\n====== RIDE SHARING DISPATCH SYSTEM ======\n";
        cout << "1. Add Driver\n";
        cout << "2. Add Rider & Request Trip\n";
        cout << "3. Assign Driver to Trip\n";
        cout << "4. Show Trips\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // -------- ADD DRIVER --------
        if (choice == 1) {
            string name, city, zone;

            cout << "Enter Driver Name: ";
            cin >> name;

            cout << "Enter Driver City: ";
            cin >> city;

            cout << "Enter Driver Zone: ";
            cin >> zone;

            Driver* d = new Driver(++driverId, name, city, zone);
            drivers.push_back(d);
            engine.addDriver(d);

            cout << "Driver added successfully.\n";
        }

        // -------- ADD RIDER & REQUEST TRIP --------
        else if (choice == 2) {
            string name, pickup, drop;

            cout << "Enter Rider Name: ";
            cin >> name;

            cout << "Enter Pickup Location: ";
            cin >> pickup;

            cout << "Enter Dropoff Location: ";
            cin >> drop;

            Rider* r = new Rider(++riderId, name, pickup, drop);
            riders.push_back(r);

            Trip* t = new Trip(++tripId, r);
            trips.push_back(t);

            cout << "Trip requested successfully. Trip ID: " << tripId << endl;
        }

        // -------- ASSIGN DRIVER --------
        else if (choice == 3) {
            int id;
            cout << "Enter Trip ID: ";
            cin >> id;

            if (id > 0 && id <= (int)trips.size()) {
                Driver* d = engine.findDriverForTrip(trips[id - 1]);

                if (d != nullptr) {
                    cout << "Driver Assigned: " << d->getName() << endl;
                } else {
                    cout << "No available driver found.\n";
                }
            } else {
                cout << "Invalid Trip ID.\n";
            }
        }

        // -------- SHOW TRIPS --------
        else if (choice == 4) {
            for (int i = 0; i < (int)trips.size(); i++) {
                cout << "\nTrip ID: " << trips[i]->getTripId();
                cout << "\nRider: " << trips[i]->getRider()->getname();

                if (trips[i]->getDriver() != nullptr)
                    cout << "\nDriver: " << trips[i]->getDriver()->getName();
                else
                    cout << "\nDriver: Not Assigned";

                cout << "\n---------------------------\n";
            }
        }

    } while (choice != 0);

    cout << "System exited successfully.\n";
    return 0;
}
