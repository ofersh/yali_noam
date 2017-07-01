/*
 * CommandFactory.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_COMMANDFACTORY_H_
#define UTILITIES_COMMANDFACTORY_H_


#include "../Elements/Ship.h"

class Command_Factory {
public:
	enum shipCommand{COURSE,POSITION,DESTINATION,LOAD_AT,UNLOAD_AT,DOCK_AT,ATTACK,REFUEL,STOP};

	Command_Factory()=default;
	~Command_Factory()=default;



	struct CommandInfo{

			bool breakCommand(string s);

			string shipName,destination;
			Ship::Type type;
			double arg1,arg2,arg3,arg4;
		};

	Ships_commands* getShipCommand(CommandInfo cmdInfo,shipCommand sc);
};

#endif /* UTILITIES_COMMANDFACTORY_H_ */
