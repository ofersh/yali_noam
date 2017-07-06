

#include "Civil_ship.h"
#include "Port.h"
#include "../Utilities/CivilShipsCommands.h"
#include "../Utilities/CommandFactory.h"


Civil_ship::Civil_ship(Type t, string name, Point pos, double fuel,double lpm,double maxV):Ship(t,name,pos,fuel,maxV), fuel_consumption(lpm),fuelling(false)
{
}

//Dock at destination port, if not in range move to it.
bool Civil_ship::dock(weak_ptr<Port> port)
{
    //if not current destination, start to move toward destination.
    if (destination.lock()!=port.lock())
    {
        set_velocity(getMaxVelocity());
        setDestination(port);
        return false;
    }
    
    // try to dock.
    Point portPos=port.lock()->getPosition();
    if (Ship::inRange(portPos,DOCKING_RANGE))
    {
        Ship::set_state(State::DOCKED);
        return true;
    }
    return false; //failed to dock.
}

// fuel ship.
void Civil_ship::fuel(double fuel)
{
    Marine_Element::addFuel(fuel);
}

//for fueling purposes.
double Civil_ship::getRequiredFuelAmount()const
{
    return Marine_Element::getFuelCapcity()-Marine_Element::getCurrentFuel();
}


//set destiantion to given port.
void Civil_ship::setDestination(weak_ptr<Port> port)
{
    destination=port;
    Ship::set_route(port.lock()->getPosition());
    Ship::set_state(State::MOVING);
}

//enqueue ciivil ship commands.
void Civil_ship::enqueue(Civil_Ships_Commands *csc)
{
    Ship::enqueue(csc);
}


//add ship to fuel queue of port.
bool Civil_ship::refuel()
{
    if (Ship::get_state()==State::DOCKED)
    {
        destination.lock()->fuel_request(this);
        return true;    //entering fuel queue.
    }
    return false;   //Must be at Dock state.
}

//set fuelling flag.
void Civil_ship::set_Waiting_for_fuel(bool b)
{
    fuelling=b;
}


void Civil_ship::advance(){
	if(Marine_Element::getCurrentFuel() == 0){
		Ship::set_state(Ship::State::DEAD);
		return;
	}
	Marine_Element::addFuel(-fuel_consumption);
	Ship::advance();
}
