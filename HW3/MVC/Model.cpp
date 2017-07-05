/*
 * Model.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Model.h"
#include "View.h"
#include <iostream>
#include "../Utilities/Freighter_commands.h"
#include "../Utilities/CivilShipsCommands.h"
#include "../Utilities/Cruiser_commands.h"


using namespace std;

//add a new port to model.
void Model::addPort(string port_name, double x, double y, int maxFuel, int fph)
{
	shared_ptr<Port> newPort = Port::create_port(port_name, Point(x,y), maxFuel,fph);
    elements_list.push_back(newPort);
    newPort->setObsetrver(view);
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
    for (shared_ptr<Marine_Element> &wme : elements_list)
    {
        wme->go();
    }

}

//perform status action on all elements.
void Model::status()const
{
    for (const shared_ptr<Marine_Element>& wme : elements_list)
    {
        wme->status();
    }
}

//create ship by given type.
void Model::create(string name, Ship::Type type, double x, double y, int arg1, int arg2)
{
    Shipyard & shipyard =Shipyard::get_ship_factory();
    int force=arg1,range=arg2,maxCargo=arg1,resistance=arg2;
    shared_ptr<Ship> newShip;
    switch (static_cast<int>(type)) {
        case static_cast<int> (Ship::Type::CRUISER) :
        	newShip = shipyard.build_cruiser(name, x, y, force, range);
            elements_list.push_back(newShip);
            break;
        case static_cast<int> (Ship::Type::CRUISE_SHIP) :
        	newShip = shipyard.build_cruise_ship(name, x, y);
            elements_list.push_back(newShip);
            break;
        case static_cast<int> (Ship::Type::FREIGHTER) :
        	newShip = shipyard.build_freighter(name, x, y, maxCargo, resistance);
            elements_list.push_back(newShip);
            break;
        default:
            break;
    }
    newShip->setObsetrver(view);
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


void Model::setView(shared_ptr<View> v){
	view = v;
    v->refresh();
}

