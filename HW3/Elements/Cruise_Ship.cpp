
#include "Cruise_Ship.h"
#include "Port.h"
#include "Utilities/CivilShipsCommands.h"



Cruise_Ship::Cruise_Ship(Type t, string name, coordinates pos, double fuel):Civil_ship(t, name ,pos ,MAXFUEL, LPM),waiting_for_action(true)
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
