/*
 * Ship.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */


#include "Ship.h"



Ship::Ship(Type t, string name, int x, int y, double fuel):Marine_Element(name,x,y,fuel), state(STOPPED),scouter(x,y)
{}



//stop the ship
void Ship::halt()
{
    state=STOPPED;
}

//add a command to ship command queue.
void Ship::enqueue(Ships_commands *sc)
{
    command_queue.push(shared_ptr<Ships_commands>(sc));

}

//calculate route to current destination.
void Ship::calculate_route()
{
    /***** TODO IMPLEMENT ****/
}


//set the direction to head.
void Ship::set_direction(double arg){
    scouter.setAzimuth(arg);
}


//set ship velocity.
void Ship::set_velocity(double v){
    scouter.setVelocity(v);
}







