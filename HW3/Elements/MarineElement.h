/*
 * MarineElement.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef MARINEELEMENT_H_
#define MARINEELEMENT_H_

#include <utility>
#include <string>


using std::pair;
using std::string;

using coordinates = pair<int, int>; //VERY IMPORTANT, FIRST Y THEN X.

class Marine_Element {

private:
    string name;
    coordinates position; // position in the seven seas.
    
    double fuel_tank_capacity;
    double current_fuel;
    
    
public:
	Marine_Element(string name, int x, int y, double fuel);
	virtual ~Marine_Element()=0;
    
    coordinates getPosition() const {return position;};
    void setPosition(int x, int y){ position.first=y; position.second=x;};

    double getFuelCapcity()const{return fuel_tank_capacity;};
    double getCurrentFuel()const{return current_fuel;};
    double getRquiredFuelAmount()const{return fuel_tank_capacity-current_fuel;};
    void fuel(double fuel){current_fuel+=fuel;};
    
    virtual void go()=0;
    
};

#endif /* MARINEELEMENT_H_ */
