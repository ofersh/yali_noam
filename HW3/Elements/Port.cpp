/*
 * Port.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Port.h"
#include "Freighter.h"
#include <iostream>

using namespace std;


Port::Port(string name, coordinates pos, double fuel):Marine_Element(name,pos,fuel)
{
}

Port::~Port() {
	// TODO Auto-generated destructor stub
}

// The  only way to get port is to use this function.
shared_ptr<Port> Port::create_port(string name, coordinates pos, double fuel)
{
    shared_ptr<Port> sp{new Port(name,pos,fuel)};
    ports_list.push_back(sp);
    return sp;
}


//rcieve amount of containers from ship.
void Port::unload_ship(unsigned int amount)
{
    containers+=amount;
}


//load given ship with cargo.
void Port::load_ship(Freighter &fr)
{
    unsigned int amount=fr.empty_space();
    
    if (containers<amount)
        amount=containers;
        
    fr.add_cargo(amount);
}


//adding ship to fuel request.
void Port::fuel_request( Civil_ship* ship)
{
    fuel_queue.push(ship);
    ship->set_Waiting_for_fuel(true);
}


// fullfill fuel request by FIFO.
void Port::go()
{
    Civil_ship * ship_to_fuel=fuel_queue.front();
    fuel_queue.pop();
    double amount=ship_to_fuel->getRquiredFuelAmount();
    double availble=Marine_Element::getCurrentFuel();
    if (amount>availble)
        amount=availble;
    ship_to_fuel->fuel(amount);
    ship_to_fuel->set_Waiting_for_fuel(false);
}





