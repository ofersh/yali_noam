/*
 * Ship.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */


#include "Ship.h"
#include "../Utilities/Ships_commands.h"



Ship::Ship(Type t, string name,Point pos, double fuel,double maxV):Marine_Element(name,pos,fuel), state(STOPPED),maxVelocity(maxV)
{}



//stop the ship
void Ship::halt()
{
    state=STOPPED;
}

//add a command to ship command queue.
void Ship::enqueue(Ships_commands *sc)
{
    command_queue.push_back(shared_ptr<Ships_commands>(sc));

}


//set the direction to head.
void Ship::set_direction(double arg){
    scouter.setAzimuth(arg);
}


//set ship velocity.
void Ship::set_velocity(double v){
    scouter.setVelocity(v);
}

void Ship::set_route(Point dest){
	scouter.setAzimuth(Marine_Element::getPosition(),dest);
	scouter.setDestination(dest);
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
    command_queue.pop_front();
}


bool Ship::inRange(Point p,double range){
	double actualRange = scouter.calculate_distance(Marine_Element::getPosition(),p);
	if(actualRange > range)
		return false;
	return true;
}

void Ship::advance(){
	Point currentPos = Marine_Element::getPosition();
	Point nextPos = scouter.calculateNextStep(currentPos);
	if(nextPos == scouter.getDestCoordinates())
		set_state(State::STOPPED);
	Marine_Element::setPosition(nextPos.x,nextPos.y);
}

