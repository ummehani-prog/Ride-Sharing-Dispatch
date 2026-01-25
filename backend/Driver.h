#ifndef DRIVER_H
#define DRIVER_H

#include <string>
using namespace std;

class Driver {
private:
    int id;             
    string name;       
    string location;   
    string Zone;        
    bool available;    
    int completedTrips; 

public:
    
    Driver(int driverId, string driverName, string loc, string zone);

    int getId() const;
    string getName() const;
    string getLocation() const;
    string getZone() const;
    bool isAvailable() const;
    int getCompletedTrips() const;

    void setLocation(string loc);
    void setAvailable(bool status);
    void incrementTrips();
    void decrementTrips();
};

#endif