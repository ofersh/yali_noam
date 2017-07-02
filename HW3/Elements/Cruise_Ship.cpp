
#include "Cruise_Ship.h"
#include "Port.h"
#include "../Utilities/CivilShipsCommands.h"
#include <iostream>

using namespace std;


Cruise_Ship::Cruise_Ship(Type t, string name, Point pos):Civil_ship(t, name ,pos ,MAXFUEL, LPM),waiting_for_action(true)
{
    remainingPorts=Port::get_port_list();
}

Cruise_Ship::~Cruise_Ship() {
	// TODO Auto-generated destructor stub
}

//cruise ship go command.
void Cruise_Ship::go()
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
    
    //ship is doing nothing. move to next destination.
    findNextPort();
    weak_ptr<Port> new_dest=Civil_ship::get_destination();
    
    //check if there is a target port.
    if (new_dest.expired())
        return;
    
    //enqueue new commands.
    Dock_at *next_stop= new Dock_at{new_dest};
    Refuel *next_refuel= new Refuel{};

    Civil_ship::enqueue(next_stop);
    if (remainingPorts.size()!=1)
      Civil_ship::enqueue(next_refuel);
}


//print cruis ship status.
void Cruise_Ship::status()const
{
    Point mypos=Marine_Element::getPosition();
    weak_ptr<Port>myDest=Civil_ship::get_destination();
    Ship::State myState=Ship::get_state();
    
    cout<<"Cruise_ship "<<Marine_Element::getName()<<" at ";
    mypos.print();
    cout<<" fuel: "<<Ship::getCurrentFuel()<<" kl ";
    if (myState==Ship::State::MOVING)
    {
        cout<<"Moving to "<<myDest.lock()->getName()<<" on course "<<Ship::getAzimuth()<<"deg, speed "<<Ship::getVelocity()<<" nm/hr";
    }else if(myState== Ship::State::DOCKED){
        cout<<"Docking at "<< myDest.lock()->getName();
    }else if(myState==Ship::State::STOPPED)
        cout<<"Stopped";
    else if (myState==Ship::State::DEAD)
        cout<<"Dead in the water";
    
    cout<<endl;
}
