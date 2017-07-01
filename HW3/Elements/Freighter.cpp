/*
 * Freighter.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Freighter.h"

Freighter::Freighter(int maxCont, int res,Ship::Type t, string name, int x, int y, double fuel):Ship(t, name, x, y, fuel), maxCargo(maxCont), container(maxCont), resistence(res)
{}


void Freighter::dock(weak_ptr<Port> pname)
{
    setDestination(pname);
    if ()
}



Freighter::~Freighter() {
	// TODO Auto-generated destructor stub
}

