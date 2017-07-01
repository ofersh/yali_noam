/*
 * CommandFactory.cpp
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#include "CommandFactory.h"
#include "Cruiser_commands.h"
#include "Freighter_commands.h"
#include "../MVC/Model.h"
#include <sstream>
#include <algorithm>

using namespace std;
using CommandInfo::shipCommand;


Ships_commands* Command_Factory::getShipCommand(CommandInfo cmdInfo){
	Model m = Model::getModel();

	if(m.getShip(cmdInfo.shipName) == nullptr)
		return nullptr;

	double arg,velocity;
	int x,y;
	switch (static_cast<int>(cmdInfo.shipCMD)) {
		case static_cast<int>(shipCommand::COURSE):
			arg = cmdInfo.arg1;
			velocity = cmdInfo.arg2;
			return new Course(arg,velocity);

		case static_cast<int>(shipCommand::POSITION):
			x = cmdInfo.arg1;
			y = cmdInfo.arg2;
			velocity = cmdInfo.arg3;
			return new Positon(x,y,velocity);

		case static_cast<int>(shipCommand::DESTINATION):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			velocity = cmdInfo.arg1;
			weak_ptr<Port> destPort = m.getPort(cmdInfo.destination);
			if(destPort.expired())
				return nullptr;
			return new Destination(destPort,velocity);

		case static_cast<int>(shipCommand::LOAD_AT):
			if(cmdInfo.type != Ship::Type::FREIGHTER)
				return nullptr;
			weak_ptr<Port> destPort = m.getPort(cmdInfo.destination);
			if(destPort.expired())
				return nullptr;
			return new Load_at(destPort);


		case static_cast<int>(shipCommand::UNLOAD_AT):
			if(cmdInfo.type != Ship::Type::FREIGHTER)
				return nullptr;
			int amount = cmdInfo.arg1;
			weak_ptr<Port> destPort = m.getPort(cmdInfo.destination);
				if(destPort.expired())
					return nullptr;
			return new Unload_at(destPort,amount);

		case static_cast<int>(shipCommand::DOCK_AT):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			velocity = cmdInfo.arg1;
			weak_ptr<Port> destPort = m.getPort(cmdInfo.destination);
				if(destPort.expired())
					return nullptr;
			return new Destination(destPort,velocity);

		case static_cast<int>(shipCommand::ATTACK):
			if(cmdInfo.type != Ship::Type::CRUISER)
				return nullptr;
			weak_ptr<Port> destShip = m.getShip(cmdInfo.destination);
				if(destShip.expired())
					return nullptr;
			return new Attack(destShip);

		case static_cast<int>(shipCommand::REFUEL):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			return Refuel();

		case static_cast<int>(shipCommand::STOP):
			return Stop();

		default:
			break;
	}

	return nullptr;
}

