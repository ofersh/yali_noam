
#ifndef UTILITIES_COMMANDFACTORY_H_
#define UTILITIES_COMMANDFACTORY_H_


#include "../Elements/Ship.h"
#include "CivilShipsCommands.h"
#include "Freighter_commands.h"
#include "Cruiser_commands.h"
#include "CommandInfo.h"

class Port;
class Model;

class Command_Factory {
public:

	static Command_Factory& getCommandFactory();

	Ships_commands* getShipCommand(CommandInfo cmdInfo);

	// ship commands
	Ships_commands* get_Course_Command(double arg, double v);
	Ships_commands* get_Position_Command(double x,double y, double v);
	Ships_commands* get_Stop_Command();

	// civil ship commands
	Civil_Ships_Commands* get_Destination_Command(weak_ptr<Port> port_name,double velocity);
	Civil_Ships_Commands* get_Dock_at_Command(weak_ptr<Port> port_name);
	Civil_Ships_Commands* get_Refuel_Command();

	// freighter commands
	Freighter_commands* get_Load_at_Command(weak_ptr<Port> port_name);
	Freighter_commands* get_UnLoad_at_Command(weak_ptr<Port> port_name,int amount);

	//cruiser commands
	Cruiser_commands* get_Attack_Command(weak_ptr<Ship> ship_name);


private:
	weak_ptr<Port> getLegalPort(string name, Model& m);

	Command_Factory()=default;
	~Command_Factory()=default;
};

#endif /* UTILITIES_COMMANDFACTORY_H_ */
