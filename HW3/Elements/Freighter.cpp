#include "Freighter.h"
#include <iostream>
#include "Cruiser.h"
#include "../Utilities/CommandFactory.h"
#include "Port.h"


using namespace std;


Freighter::Freighter(string name, Point pos,unsigned int maxCont, int res):\
		Civil_ship(Ship::Type::FREIGHTER,name, pos, MAXFUEL,LPM,MAXVELOCITY), current_containers(0) , maxCargo(maxCont), resistence(res)
{}

Freighter::~Freighter() {}

//enqueue freighter command to queue.
void Freighter::enqueue(Freighter_commands *csc){
    Civil_ship::enqueue(csc);
}


// unload containers at port.
bool Freighter::disembark(weak_ptr<Port> port, unsigned int amount)
{
    // cant disambark without DOCKED stated.
    if (Civil_ship::dock(port))
    {
        if (amount>current_containers){
            cerr<<"cant unload: "<<amount<<" containers. unloading: "<<current_containers<<endl;
            amount=current_containers;
        }
        current_containers-=amount;
        return true;
    }
    return false;
}


// load containers to ship.
bool Freighter::embark(weak_ptr<Port> port)
{
    //Must dock before embark
    if (Civil_ship::dock(port)){
        port.lock()->load_ship(*this);
        return true;
    }
    return false;
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

//return ship type.
Ship::Type Freighter::getType()const{
	return Ship::Type::FREIGHTER;
}

//print freighter status
void Freighter::status()const
{
    Point myPos=Marine_Element::getPosition();
    Ship::State myStatus=Ship::get_state();
    weak_ptr<Port> myDest=Civil_ship::get_destination();
    
    cout<<"Freighter "<<Marine_Element::getName()<<" at ";
    myPos.print();
    cout.precision(7);
    cout<<", fuel: "<<Marine_Element::getCurrentFuel()<<" kl, resistence: "<<resistence;
    
    if (myStatus==Ship::State::MOVING)
    {
        cout<<" Moving to "<<myDest.lock()->getName()<<" on course "<<getAzimuth()<<" deg, speed "<<getVelocity()<<" nm/hr, Containers: "<<current_containers<<", moving to loading destination."<<endl;
    }else if (myStatus==Ship::State::DOCKED)
    {
        cout<<" Docking at "<<myDest.lock()->getName()<<", Containers: "<<current_containers<<endl;
    }else if (myStatus==Ship::State::STOPPED)
    {
        cout<<" Stopped, Containers: "<<current_containers<<endl;;
    }
    else if (myStatus==Ship::State::DEAD)
    {
        cout<<" Dead in the water, Containers: "<<current_containers<<endl;;
    }
    
}


//freighter next step.
void Freighter::go()
{
    //as long as ship is moving, keep on moving.
    if (Ship::get_state()==Ship::MOVING)
        Ship::advance();
    
    shared_ptr<Ships_commands> nextCMD=Ship::getNextCommand();     //get next command.
    
    if (Civil_ship::isFuelling())    //check if waiting for fuel.
        return;
    
    if (nextCMD!=nullptr)    //first try to perform Command in queue.
    {
        if (nextCMD->operator()(this))
            Ship::dequeue_command();    //upon success dequeue command.
        return;
    }

}



