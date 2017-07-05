/*
 * MarineElement.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "MarineElement.h"



Marine_Element::Marine_Element(string name, Point pos , double fuel):name(name),position(pos),fuel_tank_capacity(fuel),current_fuel(fuel)
{
}


void Marine_Element::addFuel(double fuel)
{
    if (current_fuel+fuel>fuel_tank_capacity)
        current_fuel=fuel_tank_capacity;
}
