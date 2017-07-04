/*
 * PirateShip.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Cruiser.h"
#include "Civil_ship.h"

#include <iostream>

using namespace std;

Cruiser::Cruiser(Type t, string name, Point pos , int force, double range):Ship(t,name, pos, -1,-1) {
	// TODO Auto-generated constructor stub

}

Cruiser::~Cruiser() {
	// TODO Auto-generated destructor stub
}

// invoke double dispatch chain, at end one of 2 attack method will perform.
bool Cruiser::attack(weak_ptr<Civil_ship> target)
{
    return (target.lock())->under_attack(this);
}

//print cruiser status.
void Cruiser::status()const
{
    Point mypos=Marine_Element::getPosition();
    cout<<"Cruiser "<<Marine_Element::getName()<<" at ";
    mypos.print();
    cout<<" force: "<<force<<", Moving on course  "<<Ship::getAzimuth()<<" deg, speed "<<Ship::getVelocity()<<" nm/hr" <<endl;
}


Ship::Type getType(){ return Ship::Type::CRUISER; }
