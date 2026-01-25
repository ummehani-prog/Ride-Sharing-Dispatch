#include "Driver.h"
Driver::Driver(int driverId, string drivername,string loc,string zone){
    id = driverId;
    name = drivername;
    location = loc;
    Zone = zone;
    available = true;
    completedTrips = 0;
}

int Driver::getId() const{
    return id;
}

string Driver::getName() const{
    return name;
}
string Driver::getLocation() const{
    return location;
}
string Driver::getZone() const{
    return Zone;
}
bool Driver::isAvailable() const{
return available;
}
int Driver:: getCompletedTrips() const{
    return completedTrips;
}

void Driver::setLocation(string loc){
 location = loc;
}
void Driver::setAvailable(bool status){
available = status;
}
void Driver::incrementTrips(){
completedTrips++;
}
void Driver::decrementTrips(){
    if (completedTrips > 0) completedTrips--;
}