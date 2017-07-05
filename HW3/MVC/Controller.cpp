/*
 * Controller.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Controller.h"
#include "Model.h"
#include "../Utilities/BadInputException.h"
#include "../Utilities/CommandFactory.h"

#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

// get the input file of the ports and set the new ports in the map
void Controller::initialize(string fileName) {
	try{
		// open file
		ifstream portFile{fileName};
		if(!portFile.is_open())
			throw OpenFileException(fileName);

		// create all the ports
		Model m = Model::getModel();
		// needed variables to create a port
		string name,line;
		double x,y;
		int maxFuel,fph;

		while(getline(portFile,line)){
			getPortDetails(line,name,x,y,maxFuel,fph);
			m.addPort(name,x,y,maxFuel,fph);
		}

	}catch (OpenFileException& e) {
		e.what();
		exit(1);
	}catch (BadInputException& e) {
		e.what();
		exit(1);
	}
}

void Controller::getPortDetails(string line,string& name,double& x,double& y,int& maxFuel,int& fph){

	stringstream ss(line);
	string buffer;

	// get the name
	getline(ss,buffer,' ');
	name = buffer;
	// get x coordinate
	getline(ss,buffer,' ');
	CommandInfo::getXCoordinate(buffer,x);
	// get y coordinate
	getline(ss,buffer,' ');
	CommandInfo::getYCoordinate(buffer,y);
	// get maximum fuel capacity
	getline(ss,buffer,' ');
	CommandInfo::getInt(buffer,maxFuel);
	// get amount of fuel fill per hour
	getline(ss,buffer,' ');
	CommandInfo::getInt(buffer,fph);

}




// run the command prompt with the user
void Controller::run(){

	string cmdLine;
	CommandInfo cmdI;
	bool running = true;

	while(running){
		cout << "enter command" << endl;
		getline(cin,cmdLine);		// read the line from the prompt
		try {

			cmdI.breakCommand(cmdLine);

			CommandInfo::CommandSection cmdType = cmdI.cmdSec;
			switch (static_cast<int>(cmdType)) {
				case static_cast<int>(CommandInfo::CommandSection::MODEL):
					handle_model_cmd(cmdI);
					break;
				case static_cast<int>(CommandInfo::CommandSection::VIEW):
					handle_view_cmd(cmdI);
					break;
				case static_cast<int>(CommandInfo::CommandSection::SHIP):
					handle_ship_cmd(cmdI);
					break;
				case static_cast<int>(CommandInfo::CommandSection::QUIT):
					running = false;
					break;
				default:
					throw BadInputException("somethimg went wrong. needed to catch before");
			}
		} catch (BadInputException& e) {
			cout << e.err << endl;
			continue;
		}

	}

}




/*** command handles ****/

void Controller::handle_model_cmd(CommandInfo& cmd){
	Model& m = Model::getModel();

    switch (static_cast<int>(cmd.cmd)) {
		case static_cast<int>(CommandInfo::Commands::STATUS):
			m.status();
			break;
		case static_cast<int>(CommandInfo::Commands::GO):
			m.go();
			break;
		case static_cast<int>(CommandInfo::Commands::CREATE):
			if(!(m.getShip(cmd.shipName).expired())) 	// check if ship already exists
				throw BadInputException("ship already exists");

			//x = cmd.arg1; y = cmd.arg2; res = cmd.arg3; force = cmd.arg4
			m.create(cmd.shipName,cmd.type,cmd.arg1,cmd.arg2,cmd.arg3,cmd.arg4);
			break;
		default:
			throw BadInputException("command has not been properly handled");
	}
}

void Controller::handle_view_cmd(CommandInfo& cmd){
	unsigned int size,ratio,x,y;
	switch (static_cast<int>(cmd.cmd)) {
	case static_cast<int>(CommandInfo::Commands::DEFAULT):
									view._default();
	break;
	case static_cast<int>(CommandInfo::Commands::SIZE):
									size = cmd.arg1;
	view.size(size);
	break;
	case static_cast<int>(CommandInfo::Commands::ZOOM):
									ratio = cmd.arg1;
	view.zoom(ratio);
	break;
	case static_cast<int>(CommandInfo::Commands::PAN):
									x = cmd.arg1; y = cmd.arg2;
	view.pan(x,y);
	break;
	case static_cast<int>(CommandInfo::Commands::SHOW):
									view.show();
	break;
	default:
		throw BadInputException("command has not been properly handled");
	}

}

void Controller::handle_ship_cmd(CommandInfo& cmd){

	Model& m = Model::getModel();
	Command_Factory& cmdFactory = Command_Factory::getCommandFactory();

	Ships_commands* command = cmdFactory.getShipCommand(cmd);
	m.addCommand(cmd.shipName,command);

}


