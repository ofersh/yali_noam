

#include "Cruiser.h"
#include "Civil_ship.h"
#include "Freighter.h"
#include "Cruise_Ship.h"
#include "../Utilities/Ships_commands.h"


#include <iostream>

using namespace std;

Cruiser::Cruiser(string name, Point pos , int force, double range):	\
		Ship(Ship::Type::CRUISER,name, pos, -1,MAXVELOCITY),force(force),range(range) {}

Cruiser::~Cruiser() {}

void Cruiser::go(){

	if (Ship::get_state()==Ship::MOVING)
			Ship::advance();

	shared_ptr<Ships_commands> nextCMD=Ship::getNextCommand();     //get next command.
    if (nextCMD!=nullptr)
        if (nextCMD->operator()(this))
            dequeue_command();
}


// invoke double dispatch chain, at end one of 2 attack method will perform.
bool Cruiser::attack(weak_ptr<Civil_ship> target)
{
    return (target.lock())->under_attack(this);
}

bool Cruiser::attack(Freighter* target)
{
	// check if ship is in range
	Point targetPos = dynamic_cast<Marine_Element*>(target)->getPosition();
	if(!Ship::inRange(targetPos,range))
		return false;

	if(force > target->getResistance()){
		force++;
		return true;
	}else
		force--;

	return false;
}

bool Cruiser::attack(Cruise_Ship* target)
{
	// check if ship is in range
	Point targetPos = dynamic_cast<Marine_Element*>(target)->getPosition();
	if(!Ship::inRange(targetPos,range))
		return false;

	return true;
}

//print cruiser status.
void Cruiser::status()const
{
    Point mypos=Marine_Element::getPosition();
    Ship::State myStatus=Ship::get_state();
    cout<<"Cruiser "<<Marine_Element::getName()<<" at ";
    mypos.print();
    cout<<" force: "<<force;
    if (myStatus==Ship::State::MOVING)
    {
        cout.precision(1);
        cout<< " Moving on course "<<getAzimuth()<<" deg, speed "<<getVelocity()<<" nm/hr "<<endl;
    }else if (myStatus==Ship::State::STOPPED)
    {
        cout<<" Stopped."<<endl;
    }
    else if (myStatus==Ship::State::DEAD)
    {
        cout<<" Dead in the water."<<endl;
    }
}


Ship::Type Cruiser::getType()const{
	return Ship::Type::CRUISER;
}

