/*
 * MarineElement.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef ELEMENTS_MARINEELEMENT_H_
#define ELEMENTS_MARINEELEMENT_H_

#include <utility>
#include <string>
#include "../Utilities/Scouter.h"

using std::pair;
using std::string;

class Marine_Element {

private:
    string name;
    Point position; // position in the seven seas.
    
    double fuel_tank_capacity;
    double current_fuel;
    
    
public:
	Marine_Element(string name, Point pos, double fuel);
	
    //must be implemented.
    virtual ~Marine_Element()=0;
    virtual void status()const =0;
    virtual void go()=0;

    //setters and getters.
    Point getPosition() const {return position;};
    void setPosition(double x, double y){ Point(x,y);};
    string getName()const{return name;};
    double getFuelCapcity()const{return fuel_tank_capacity;};
    double getCurrentFuel()const{return current_fuel;};
    void addFuel(double fuel){current_fuel+=fuel;};
};

#endif /* MARINEELEMENT_H_ */
