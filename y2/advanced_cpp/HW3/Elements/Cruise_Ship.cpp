
#include "Cruise_Ship.h"
#include "Port.h"
#include "Cruiser.h"
#include "../Utilities/CommandFactory.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

using itPort = vector<weak_ptr<Port>>::iterator;

Cruise_Ship::Cruise_Ship(string name, Point pos):Civil_ship(Ship::Type::CRUISE_SHIP, name ,pos ,MAXFUEL, LPM,MAXVELOCITY),waiting_for_action(true)
{
	remainingPorts=Port::get_port_list();
}

Cruise_Ship::~Cruise_Ship() {}


//perform double dispatch.
bool Cruise_Ship::under_attack(Cruiser *attacking){
	if(attacking->attack(this)){
		Ship::halt();
		return true;
	}
	return false;
}

//cruise ship go command.
void Cruise_Ship::go()
{
    
    
	// if the ship has finished its route
	if(remainingPorts.empty() && Ship::get_state() != Ship::State::STOPPED)
		Ship::set_state(Ship::State::STOPPED);

	


	if (Civil_ship::isFuelling())    //check if waiting for fuel.
		return;
    shared_ptr<Ships_commands> nextCMD=Ship::getNextCommand();     //get next command.
	if (nextCMD!=nullptr)    //first try to perform Command in queue.
	{
        if (nextCMD->operator()(this)){
			Ship::dequeue_command();    //upon success dequeue command.
            return;
        }
	}

    //as long as ship is moving, keep on moving, and out.
    if (Ship::get_state()==Ship::MOVING){
        Ship::advance();
        return;
    }
    
    
    //ship is doing nothing. move to next destination.
	findNextPort();
	weak_ptr<Port> new_dest=Civil_ship::get_destination();

	//check if there is a target port.
	if (new_dest.expired())
		return;

	//enqueue new commands.
	Civil_Ships_Commands *next_stop= Command_Factory::getCommandFactory().get_Dock_at_Command(new_dest);
	Civil_Ships_Commands *next_refuel= Command_Factory::getCommandFactory().get_Refuel_Command();

	Civil_ship::enqueue(next_stop);
	if (remainingPorts.size()!=1)
		Civil_ship::enqueue(next_refuel);
	else
		delete next_refuel;
}


//print cruis ship status.
void Cruise_Ship::status()const
{
	Point mypos=Marine_Element::getPosition();
	weak_ptr<Port>myDest=Civil_ship::get_destination();
	Ship::State myState=Ship::get_state();

	cout<<"Cruise_ship "<<Marine_Element::getName()<<" at ";
	mypos.print();
    cout.precision(1);
	cout<<" fuel: "<<Ship::getCurrentFuel()<<" kl ";
    cout.precision(1);
	if (myState==Ship::State::MOVING)
	{
		cout<<"Moving to "<<myDest.lock()->getName()<<" on course "<<Ship::getAzimuth()<<" deg, speed "<<Ship::getVelocity()<<" nm/hr";
	}else if(myState== Ship::State::DOCKED){
		cout<<"Docking at "<< myDest.lock()->getName();
	}else if(myState==Ship::State::STOPPED)
		cout<<"Stopped";
	else if (myState==Ship::State::DEAD)
		cout<<"Dead in the water";

	cout<<endl;
}


//return type of ship.
Ship::Type Cruise_Ship::getType()const{ return Ship::Type::CRUISE_SHIP; }


void Cruise_Ship::findNextPort(){
    // wait for first command
    if(get_destination().expired())
        return;
    
    // if no more ports to go, return.
    if (remainingPorts.empty()){
        setDestination(weak_ptr<Port>());
        return;
    }
    
	// initialize closest port
	Point shipPos = Marine_Element::getPosition();
	itPort nearestDest;
    double nearestDist = numeric_limits<double>::max();

	for (itPort it = remainingPorts.begin(); it != remainingPorts.end(); ++it) {
		// get distance between a port and  the ship
		if((*it).expired())
			continue;
        if ((*it).lock()==Civil_ship::get_destination().lock())
        {
            remainingPorts.erase(it);	// if discover port already visited, remove it.
            continue;
        }
        
		shared_ptr<Port> currentP = (*it).lock();
		Point portPos = currentP->getPosition();
		double currentDist = distance_between_two_points(shipPos,portPos);

		// check if current port is the nearest
		if(currentDist < nearestDist){
			nearestDest = it;
			nearestDist = currentDist;
		}
	}
    
    
    if (nearestDest==remainingPorts.end()) //if no destination found make destination null.
    {
        setDestination(weak_ptr<Port>());
        return;
    }
	setDestination((*nearestDest));		// set course to closest port
	remainingPorts.erase(nearestDest);	// remove the port from the list

}

