

#include "MarineElement.h"
#include "../MVC/View.h"


Marine_Element::Marine_Element(string name, Point pos , double fuel):\
				name(name),position(pos),fuel_tank_capacity(fuel),current_fuel(fuel),observer()
{}


void Marine_Element::addFuel(double fuel)
{
    if (current_fuel+fuel>fuel_tank_capacity)
        current_fuel=fuel_tank_capacity;
}

void Marine_Element::setObsetrver(weak_ptr<View> v){
	observer = v;
}

void Marine_Element::setPosition(double x, double y){
	Point oldPos = position, newPos = Point{x,y};
	position = newPos;

	if(!observer.expired())
		observer.lock()->updatePosition(name.substr(0,2),oldPos,newPos);
}

