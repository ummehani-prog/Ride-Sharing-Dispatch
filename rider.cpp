#include "rider.h"

rider::rider(int riderid,string ridername,string pickup, string dropoff){
    ID = riderid;
    Name = ridername;
    Pickuploc = pickup;
    Dropoffloc = dropoff;
}

int rider::getId() const{
return ID;
}
string rider::getname() const{
    return Name;
}
string rider::getpickup() const{
    return Pickuploc;
}
string rider:: getdropoff() const{
    return Dropoffloc;
}
void rider::setpickup(string pickup){
Pickuploc = pickup;
}
void rider::setdropoff(string dropoff){
    Dropoffloc = dropoff;
}

