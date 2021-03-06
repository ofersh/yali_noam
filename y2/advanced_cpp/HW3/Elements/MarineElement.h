
#ifndef ELEMENTS_MARINEELEMENT_H_
#define ELEMENTS_MARINEELEMENT_H_

#include <utility>
#include <string>
#include <memory>
#include "../Utilities/Scouter.h"

using std::pair;
using std::string;
using std::weak_ptr;

class View;

class Marine_Element {

private:
    string name;
    Point position; // position in the seven seas.
    
    double fuel_tank_capacity;
    double current_fuel;
    weak_ptr<View> observer;
    
    
public:
	Marine_Element(string name, Point pos, double fuel);
	
    //must be implemented.
    virtual ~Marine_Element()=default;
    virtual void status()const =0;
    virtual void go()=0;

    //setters and getters.
    void setObsetrver(weak_ptr<View> v);
    Point getPosition() const {return position;};
    void setPosition(double x, double y);
    string getName()const{return name;};
    double getFuelCapcity()const{return fuel_tank_capacity;};
    double getCurrentFuel()const{return current_fuel;};
    void addFuel(double fuel);
};

#endif /* MARINEELEMENT_H_ */
