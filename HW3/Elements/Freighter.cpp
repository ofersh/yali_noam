/*
 * Freighter.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Freighter.h"
#include <iostream>
#include "Cruiser.h"
#include "../Utilities/Freighter_commands.h"
#include "Port.h"


using namespace std;


Freighter::Freighter(unsigned int maxCont, int res,Ship::Type t, string name, Point pos, double fuel, weak_ptr<Port> dest_port):Civil_ship(t, name, pos, fuel,LPM ), current_containers(maxCont) , maxCargo(maxCont), resistence(res)
{}

Freighter::~Freighter() {
	// TODO Auto-generated destructor stub
}

//enqueue freighter command to queue.
void Freighter::enqueue(Freighter_commands *csc){
    Civil_ship::enqueue(csc);
}


// unload containers at port.
bool Freighter::disembark(weak_ptr<Port> port, unsigned int amount)
{
    weak_ptr<Port> dest=Civil_ship::get_destination();
    
    //in case trying to disembark on diffrent port than destination, add a new docking command.
    if (dest.lock()!=port.lock())
    {
        Dock_at *newDest=new Dock_at{dest};
        Civil_ship::pritorityCommand(newDest); //must add as first.
        return false;
    }
    
    // cant disambark without DOCKED stated.
    if (Ship::get_state()==State::DOCKED)
    {
        if (amount>current_containers){
            cerr<<"cant unload: "<<amount<<" containers. unloading: "<<current_containers<<endl;
            amount=current_containers;
        }
        port.lock()->add_containers(amount);
        return true;
    }
    return false;
}


// load containers to ship.
bool Freighter::embark(weak_ptr<Port> port)
{
    weak_ptr<Port> dest=Civil_ship::get_destination();
    //in case trying to embark on diffrent port than destination, add a new docking command.
    if (dest.lock()!=port.lock())
    {
        Dock_at *newDest=new Dock_at{dest};
        Civil_ship::pritorityCommand(newDest);  //must add as first.
        return false;
    }
    
    if (Ship::get_state()==State::DOCKED)
        port.lock()->load_ship(*this);
    return true;
}

//freighter revealing its type to attacking ship
bool Freighter::under_attack(Cruiser *attacking)
{
    if(attacking->attack(this)){
    	current_containers = 0;
    	Ship::halt();
    	return true;
    }
    return false;
}

Ship::Type getType(){ return Ship::Type::FREIGHTER; }
