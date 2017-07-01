/*
 * CommandFactory.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_COMMANDFACTORY_H_
#define UTILITIES_COMMANDFACTORY_H_


#include "../Elements/Ship.h"
#include "CommandInfo.h"


class Command_Factory {
public:

	Command_Factory()=default;
	~Command_Factory()=default;

	Ships_commands* getShipCommand(CommandInfo cmdInfo);
};

#endif /* UTILITIES_COMMANDFACTORY_H_ */
