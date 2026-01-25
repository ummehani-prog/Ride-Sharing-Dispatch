#ifndef RIDER_H
#define RIDER_H
#include <string>
using namespace std;
class Rider{
    private:
    int ID;
    string  Name;
    string Pickuploc;
    string Dropoffloc;

    public:
    Rider(int riderid, string ridername,string pickup, string dropoff);
    int getId() const;
    string getname() const;
    string getpickup() const;
    string getdropoff() const;
    void setpickup(string pickup);
    void setdropoff(string dropoff);
    


    };
#endif