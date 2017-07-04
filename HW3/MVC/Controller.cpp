/*
 * Controller.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Controller.h"
#include "Model.h"
#include "../Utilities/BadInputException.h"

#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

// get the input file of the ports and set the new ports in the map
void Controller::initialize(string fileName) {

	// open file
	ifstream portFile{fileName};
	if(!portFile.is_open())
		throw OpenFileException(fileName);

	checkValidity(portFile);	// check file for legal input

	// create all the ports
	string line;
	while(getline(portFile,line))
		create_port(line);

}


// run the command prompt with the user
void Controller::run(){

	string cmdLine;
	CommandInfo cmdI;
	bool running = true;

	while(running){
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
			e.what();
			continue;
		}

	}

}




/*** command handles ****/




void Controller::handle_model_cmd(CommandInfo& cmd){
	Model& m = Model::getModel();
	int x,y,res,force;
	switch (static_cast<int>(cmd.cmd)) {
	case static_cast<int>(CommandInfo::Commands::STATUS):
		m.status();
		break;
	case static_cast<int>(CommandInfo::Commands::GO):
		m.go();
		break;
	case static_cast<int>(CommandInfo::Commands::CREATE):
		x = cmd.arg1; y = cmd.arg2; res = cmd.arg3; force = cmd.arg4;
		m.create(cmd.shipName,cmd.type,x,y,res,force);
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

	//Model& m = Model::getModel();


	//HANDLE COURSE

	//HANDLE POSITION

	//HANDLE DESTINATION

	//HANDLE LOAD_AT

	//HANDLE UNLOAD_AT

	//HANDLE DOCK_AT

	//HANDLE ATTACK

	//HANDLE REFUEL

	//HANDLE STOP





}


