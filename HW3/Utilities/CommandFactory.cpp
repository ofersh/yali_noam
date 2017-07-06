
#include "CommandFactory.h"
#include "Cruiser_commands.h"
#include "Freighter_commands.h"
#include "../MVC/Model.h"
#include "BadInputException.h"

using namespace std;



Command_Factory& Command_Factory::getCommandFactory(){
	static Command_Factory command_factory;
	return command_factory;
}



Ships_commands* Command_Factory::getShipCommand(CommandInfo cmdInfo){
	Model m = Model::getModel();
	shared_ptr<Ship> currentShip = m.getShip(cmdInfo.shipName).lock();
	if(currentShip == nullptr)
		throw BadInputException((cmdInfo.shipName + " is not a ship or does not exist").c_str());
	cmdInfo.type = currentShip->getType();
	weak_ptr<Ship> destShip;
	switch (static_cast<int>(cmdInfo.shipCMD)) {
		case static_cast<int>(CommandInfo::shipCommand::COURSE):
			// arg1 = arg | arg2 = velocity
			return get_Course_Command(cmdInfo.arg1,cmdInfo.arg2);

		case static_cast<int>(CommandInfo::shipCommand::POSITION):
			// arg1 = x | arg2 = y | arg3 = velocity
			return get_Position_Command(cmdInfo.arg1,cmdInfo.arg2,cmdInfo.arg3);

		case static_cast<int>(CommandInfo::shipCommand::DESTINATION):
			if(cmdInfo.type == Ship::Type::CRUISER)
				throw BadInputException((cmdInfo.shipName + " is a cruiser").c_str());
			// arg1 = velocity
			return get_Destination_Command(getLegalPort(cmdInfo.destination,m),cmdInfo.arg1);

		case static_cast<int>(CommandInfo::shipCommand::LOAD_AT):
			if(cmdInfo.type != Ship::Type::FREIGHTER)
				throw BadInputException((cmdInfo.shipName + " is not a freighter").c_str());
			return get_Load_at_Command(getLegalPort(cmdInfo.destination,m));


		case static_cast<int>(CommandInfo::shipCommand::UNLOAD_AT):
			if(cmdInfo.type != Ship::Type::FREIGHTER)
				throw BadInputException((cmdInfo.shipName + " is not a freighter").c_str());
			// arg1 = amount
			return get_UnLoad_at_Command(getLegalPort(cmdInfo.destination,m),cmdInfo.arg1);

		case static_cast<int>(CommandInfo::shipCommand::DOCK_AT):
			if(cmdInfo.type == Ship::Type::CRUISER)
				throw BadInputException((cmdInfo.shipName + " is not a freighter").c_str());
			return get_Dock_at_Command(getLegalPort(cmdInfo.destination,m));

		case static_cast<int>(CommandInfo::shipCommand::ATTACK):
			if(cmdInfo.type != Ship::Type::CRUISER)
				throw BadInputException((cmdInfo.shipName + " is not a cruiser").c_str());
			destShip = m.getShip(cmdInfo.destination);
			if(destShip.expired())
				throw BadInputException((cmdInfo.destination + " does not exist anymore").c_str());
			return new Attack(destShip);

		case static_cast<int>(CommandInfo::shipCommand::REFUEL):
			if(cmdInfo.type == Ship::Type::CRUISER)
				return nullptr;
			return new Refuel();

		case static_cast<int>(CommandInfo::shipCommand::STOP):


		default:
			break;
	}

	return nullptr;
}


// ship commands
	Ships_commands* Command_Factory::get_Course_Command(double arg, double v){
		return new Course(arg,v);
	}
	Ships_commands* Command_Factory::get_Position_Command(double x,double y, double v){
		return new Positon(x,y,v);
	}
	Ships_commands* Command_Factory::get_Stop_Command(){
		return new Stop();
	}

	// civil ship commands
	Civil_Ships_Commands* Command_Factory::get_Destination_Command(weak_ptr<Port> port_name,double velocity){
		return new Destination(port_name,velocity);
	}
	Civil_Ships_Commands* Command_Factory::get_Dock_at_Command(weak_ptr<Port> port_name){
		return new Dock_at(port_name);
	}
	Civil_Ships_Commands* Command_Factory::get_Refuel_Command(){
		return new Refuel();
	}

	// freighter commands
	Freighter_commands* Command_Factory::get_Load_at_Command(weak_ptr<Port> port_name){
		return new Load_at(port_name);
	}
	Freighter_commands* Command_Factory::get_UnLoad_at_Command(weak_ptr<Port> port_name,int amount){
		return new Unload_at(port_name,amount);
	}

	//cruiser commands
	Cruiser_commands* Command_Factory::get_Attack_Command(weak_ptr<Ship> ship_name){
		return new Attack(ship_name);
	}



	weak_ptr<Port> Command_Factory::getLegalPort(string name, Model& m){
		weak_ptr<Port> destPort;
		destPort = m.getPort(name);
		if(destPort.expired())
			throw BadInputException((name + " does not exist anymore").c_str());
		return destPort;
	}




