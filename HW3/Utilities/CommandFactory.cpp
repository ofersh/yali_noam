/*
 * CommandFactory.cpp
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#include "CommandFactory.h"
#include "Cruiser_commands.h"
#include "Freighter_commands.h"


Ships_commands* Command_Factory::getShipCommand(CommandInfo cmdInfo,shipCommand sc){
	double arg,velocity;
	int x,y;
	switch (static_cast<int>(sc)) {
		case static_cast<int>(COURSE):
			arg = cmdInfo.arg1;
			velocity = cmdInfo.arg2;
			return new Course(arg,velocity);

		case static_cast<int>(POSITION):
			x = cmdInfo.arg1;
			y = cmdInfo.arg2;
			velocity = cmdInfo.arg3;
			return new Positon(x,y,velocity);

		case static_cast<int>(DESTINATION):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			velocity = cmdInfo.arg1;
			return new Destination(cmdInfo.destination,velocity);

		case static_cast<int>(LOAD_AT):
			if(cmdInfo.type == Ship::Type::FREIGHTER)
				return new Load_at(cmdInfo.destination);
			else
				return nullptr;

		case static_cast<int>(UNLOAD_AT):
			if(cmdInfo.type == Ship::Type::FREIGHTER)
				return new Unload_at(cmdInfo.destination);
			else
				return nullptr;

		case static_cast<int>(DOCK_AT):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			velocity = cmdInfo.arg1;
			return new Destination(cmdInfo.destination,velocity);

		case static_cast<int>(ATTACK):
			if(cmdInfo.type != Ship::Type::CRUISER)
				return nullptr;
			return new Ata(cmdInfo.destination);

		case static_cast<int>(REFUEL):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			return Refuel();

		case static_cast<int>(STOP):
			return Stop();

		default:
			break;
	}

	return nullptr;
}


bool Command_Factory::CommandInfo::breakCommand(string s){


	return true;
}
