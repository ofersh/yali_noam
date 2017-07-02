/*
 * CruiseShip.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Cruise_Ship.h"
#include "Port.h"
#include "Utillities/CivilShipsCommands.h"

Cruise_Ship::Cruise_Ship(Type t, string name, coordinates pos, double fuel):Civil_ship(t,name,pos,fuel),waiting_for_action(true)
{
    remainingPorts=Port::get_port_list();
}

Cruise_Ship::~Cruise_Ship() {
	// TODO Auto-generated destructor stub
}



void Cruise_Ship::go()
{
    weak_ptr<Port> my_dest;
    shared_ptr<Ships_commands> nextCMD=Ship::getNextCommand();
    
    
    //first try to perform Command in queue.
    if (nextCMD!=nullptr)
    {
        if ((*nextCMD)(this))
        {
            //upon success dequeue command.
            Ship::dequeue_command();
        }
        return;
    }
    
    //if ship is currently fuelling.
    if (Civil_ship::isFuelling())
        return;
    
    //ship is doing nothing. move to next destination.
    
    
    
    
    
    
    

}
