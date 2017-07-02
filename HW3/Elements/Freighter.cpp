/*
 * Freighter.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Freighter.h"
#include <iostream>

using namespace std;


Freighter::Freighter(unsigned int maxCont, int res,Ship::Type t, string name, coordinates pos, double fuel, weak_ptr<Port> dest_port):Civil_ship(t, name, pos, fuel), maxCargo(maxCont), current_containers(maxCont), resistence(res)
{}

Freighter::~Freighter() {
	// TODO Auto-generated destructor stub
}



// unload containers at port.
void Freighter::disembark(weak_ptr<Port> port, unsigned int amount)
{
    weak_ptr<Port> dest=Civil_ship::get_destination();
    
    if (dest.lock()!=port.lock())
    {
        Civil_ship::dock(port);
        return;
    }
        
    if (Ship::get_state()==State::DOCKED)
    {
        if (amount>current_containers){
            cerr<<"cant unload: "<<amount<<" containers. unloading: "<<current_containers<<endl;
            amount=current_containers;
        }
        port.lock()->unload_ship(amount);
    }
}


// load containers to ship.
void Freighter::embark(weak_ptr<Port> port)
{
    Civil_ship::dock(port);
    if (Ship::get_state()==State::DOCKED)
        port.lock()->load_ship(*this);
}
