#include "Rider.h"

Rider::Rider(int riderid,string ridername,string pickup, string dropoff){
    ID = riderid;
    Name = ridername;
    Pickuploc = pickup;
    Dropoffloc = dropoff;
}

int Rider::getId() const{
return ID;
}
string Rider::getname() const{
    return Name;
}
string Rider::getpickup() const{
    return Pickuploc;
}
string Rider:: getdropoff() const{
    return Dropoffloc;
}
void Rider::setpickup(string pickup){
Pickuploc = pickup;
}
void Rider::setdropoff(string dropoff){
    Dropoffloc = dropoff;
}