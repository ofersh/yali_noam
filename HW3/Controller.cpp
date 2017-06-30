/*
 * Controller.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Controller.h"
#include "Model.h"

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
	bool running = true;

	while(running){
		getline(cin,cmdLine);		// read the line from the prompt
		commandType cmdType = getCommandType(cmdLine);		// get the type of the command
		switch (cmdType) {
			case MODEL:
				handle_model_cmd(cmdLine);
				break;

			case VIEW:
				handle_view_cmd(cmdLine);
				break;

			case SHIP:
				handle_ship_cmd(cmdLine);
				break;

			case QUIT:
				running = false;
				break;

			default:
				cerr << "wrong input" << endl;
				break;
		}
	}

}




/*** command handles ****/

Controller::commandType Controller::getCommandType(string cmd){



}


void Controller::handle_model_cmd(string& cmd){
	Model& m = Model::getModel();
	stringstream ss{cmd};

	m.status();

	m.go();

	ShipInfo si(cmd);
	m.create(si.name,si.type,si.x,si.y,si.arg1,si.arg2);


}

void Controller::handle_view_cmd(string& cmd){

	//,SIZE,ZOOM,PAN,SHOW
		// DEFAULT

}

void Controller::handle_ship_cmd(string& cmd){
	Model& m = Model::getModel();
}


