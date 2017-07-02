//
//  Civil_ship.cpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "Civil_ship.h"

Civil_ship::Civil_ship(Type t, string name, coordinates pos, double fuel):Ship(t,name,pos,fuel),fuelling(false)
{
}



//Dock at destination port, if not in range move to it.
void Civil_ship::dock(weak_ptr<Port> port)
{
    //if not current destination, start to move toward detination.
    if (destination.lock()!=port.lock())
    {
        setDestination(port);
        return;
    }
    
    // try to dock.
    coordinates portPos=port.lock()->getPosition();
    if (Ship::calculate_distance(portPos) < DOCKING_RANGE)
    {
        Ship::set_state(State::DOCKED);
    }
}


//set destiantion to given port.
void Civil_ship::setDestination(weak_ptr<Port> port)
{
    destination=port;
    Ship::calculate_route();
    Ship::set_state(State::MOVING);
}

//enqueue ciivil ship commands.
void Civil_ship::enqueue(Civil_Ships_Commands *csc)
{
    Ship::enqueue(csc);
}


//add ship to fuel queue of port.
void Civil_ship::refuel()
{
    
    //might be unneccssary.
    if (Ship::get_state()==State::DOCKED)
    {
        destination.lock()->fuel_request(this);
    }
}
