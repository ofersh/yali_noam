/*
 * Model.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Model.h"
#include <iostream>
#include "../Utilities/Freighter_commands.h"
#include "../Utilities/CivilShipsCommands.h"
#include "../Utilities/Cruiser_commands.h"


using namespace std;

//add a new port to model.
void Model::addPort(string port_name, double x, double y, int maxFuel, int fph)
{
    elements_list.push_back(Port::create_port(port_name, Point(x,y), maxFuel,fph));
}


//add command to ship, polymorphicly will fall into place.
void Model::addCommand(string ship,Ships_commands* shipCmd)
{
    shared_ptr<Ship> ship_on_duty= getShip(ship).lock();
    
    
    // reveal shipCMD true id and invoke relvant enqueue command.
    if (Freighter_commands *fc =dynamic_cast<Freighter_commands*>(shipCmd))
    {
        ship_on_duty->enqueue(fc);
    }else if(Civil_Ships_Commands * csc= dynamic_cast<Civil_Ships_Commands *>(shipCmd))
    {
        ship_on_duty->enqueue(csc);
    }else if(Cruiser_commands* cc=dynamic_cast<Cruiser_commands*>(shipCmd) )
    {
        ship_on_duty->enqueue(cc);
    }

    
}


// perform go step on all elemments.
void Model::go()
{
    for (shared_ptr<Marine_Element> wme : elements_list)
    {
        wme->go();
    }

}

//perform status action on all elements.
void Model::status()const
{
    for (shared_ptr<Marine_Element> wme : elements_list)
    {
        wme->status();
    }
}

//create ship by given type.
void Model::create(string name, Ship::Type type, double x, double y, int cargo_capacity, int resistence, int force,int range)
{
    Shipyard & shipyard =Shipyard::get_ship_factory();
    
    switch (static_cast<int>(type)) {
        case static_cast<int> (Ship::Type::CRUISER) :
            elements_list.push_back(shipyard.build_cruiser(name, x, y, force, range));
            break;
        case static_cast<int> (Ship::Type::CRUISE_SHIP) :
            elements_list.push_back(shipyard.build_cruise_ship(name, x, y));
            break;
        case static_cast<int> (Ship::Type::FREIGHTER) :
            elements_list.push_back(shipyard.build_freighter(name, x, y, cargo_capacity, resistence));
            break;
        default:
            break;
    }
    
    
}


//return port by name.
weak_ptr<Port> Model::getPort(string portName)
{
    vector<weak_ptr<Port>> portList=Port::get_port_list();
    for (weak_ptr<Port> wp : portList)
    {
        if (!wp.expired())
        {
            if (wp.lock()->getName()==portName)
                return wp;
        }
    }
    return weak_ptr<Port>{};
}

//return ship by name.
weak_ptr<Ship> Model::getShip(string shipName)
{
    Shipyard & shipyard =Shipyard::get_ship_factory();
    return shipyard.findShip(shipName);
}

