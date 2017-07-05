/*
 * MarineElement.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "MarineElement.h"
#include "../MVC/View.h"


Marine_Element::Marine_Element(string name, Point pos , double fuel):\
				name(name),position(pos),fuel_tank_capacity(fuel),current_fuel(fuel),observer(nullptr)
{}


void Marine_Element::addFuel(double fuel)
{
    if (current_fuel+fuel>fuel_tank_capacity)
        current_fuel=fuel_tank_capacity;
}

void Marine_Element::setObsetrver(View* v){
	observer = v;
}

void Marine_Element::setPosition(double x, double y){
	Positon oldPos = position, newPos = Point{x,y};
	string shortName = name.substr(0,2);
	position = newPos;
	if(observer)
		observer->updatePosition(shortName,oldPos,newPos);
};

