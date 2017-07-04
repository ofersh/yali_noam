/*
 * Ship.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */


#include "Ship.h"
#include "../Utilities/Ships_commands.h"



Ship::Ship(Type t, string name,Point pos, double fuel, double lpm):Marine_Element(name,pos,fuel), state(STOPPED),fuel_consumption(lpm)
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


//get next command from command queue.
shared_ptr<Ships_commands> Ship::getNextCommand()const
{
    if (command_queue.empty())
        return shared_ptr<Ships_commands>{};
    
    return command_queue.front();;
}


//remove last command.
void Ship::dequeue_command(){
    if (command_queue.empty())
        return;
    command_queue.pop();
}


bool Ship::inRange(Point p,double range){
	double actualRange = distance_between_two_points(Marine_Element::getPosition(),p);
	if(actualRange > range)
		return false;
	return true;
}



