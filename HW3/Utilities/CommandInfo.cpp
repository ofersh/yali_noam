/*
 * CommandInfo.cpp
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#include "CommandInfo.h"
#include "BadInputException.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <array>

using namespace std;

void CommandInfo::breakCommand(string line){
	vector<string> mvCMD = {"status","go","create","default","size","zoom","pan","show","quit"};
	stringstream ss(line);
	string buffer;
	int tempArg;
	char garbage;


	getline(ss,buffer,' ');
	auto pos = find(mvCMD.begin(),mvCMD.end(),buffer) - mvCMD.begin();
	switch (pos) {
		case 0:
			cmdSec = CommandSection::MODEL;
			cmd = Commands::STATUS;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return;
		case 1:
			cmdSec = CommandSection::MODEL;
			cmd = Commands::GO;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return;
		case 2:
			cmdSec = CommandSection::MODEL;
			cmd = Commands::CREATE;
			// check validity of create command
			getline(ss,buffer);
			createConditions(buffer);
			return;
		case 3:
			cmdSec = CommandSection::VIEW;
			cmd = Commands::DEFAULT;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return;
		case 4:
			cmdSec = CommandSection::VIEW;
			cmd = Commands::SIZE;
			// check validity of size command
			getline(ss,buffer,' ');
			getInt(buffer,tempArg);
			if(tempArg<6)
				throw BadInputException("New map size is too small");
			else if(tempArg > 30)
				throw BadInputException("New map size is too big");;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			arg1 = tempArg;
			return;

		case 5:
			cmdSec = CommandSection::VIEW;
			cmd = Commands::ZOOM;
			// check validity of zoom command
			getline(ss,buffer,' ');
			getIntOrDouble(buffer,arg1);
			ss >> garbage;

			if(!ss.fail())
				throw BadInputException("extra chars in input");
			if(arg1<=0)
				throw BadInputException("ERROR: New map scale must be positive");
			return;

		case 6:
			cmdSec = CommandSection::VIEW;
			cmd = Commands::PAN;
			// check validity of pan command
			getline(ss,buffer,' ');
			getIntOrDouble(buffer,arg1);
			getline(ss,buffer,' ');
			getIntOrDouble(buffer,arg2);
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return;

		case 7:
			cmdSec = CommandSection::VIEW;
			cmd = Commands::SHOW;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return ;
		case 8:
			cmdSec = CommandSection::QUIT;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			return;
		default:
			cmdSec = CommandSection::SHIP;
			break;
	}
	shipName = buffer;
	// get the rest of the text
	getline(ss,buffer);
	return shipCommandBreak(buffer);
}


void CommandInfo::shipCommandBreak(string line){
	vector<string> shipCMDs = {"course","position","destination","load_at","unload_at","dock_at","attack","refuel","stop"};
	stringstream ss(line);
	string buffer;
	int tempArg;
	char garbage;

	getline(ss,buffer,' ');		// get the command
	auto pos = find(shipCMDs.begin(),shipCMDs.end(),buffer) - shipCMDs.begin();	// calculate which command
	switch (pos) {
	case 0:
		shipCMD = COURSE;
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg1 = tempArg;
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg2 = tempArg;
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		return;

	case 1:
		shipCMD = POSITION;
		getline(ss,buffer,' ');
		getXCoordinate(buffer,arg1);		// get x
		getline(ss,buffer,' ');
		getYCoordinate(buffer,arg2);		// get y
		getline(ss,buffer,' ');
		getDouble(buffer,arg3);				// get velocity
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		return;

	case 2:
		shipCMD = DESTINATION;
		if(!getline(ss,destination,' '))
			throw BadInputException("no destination has been entered");
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		arg1 = tempArg;
		break;

	case 3:
		shipCMD = LOAD_AT;
		if(!getline(ss,destination,' '))
			throw BadInputException("no destination has been entered");
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		break;

	case 4:
		shipCMD = UNLOAD_AT;
		if(!getline(ss,destination,' '))
			throw BadInputException("no destination has been entered");
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		arg1 = tempArg;
		break;

	case 5:
		shipCMD = DOCK_AT;
		if(!getline(ss,destination,' '))
			throw BadInputException("no destination has been entered");
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		break;
	case 6:
		shipCMD = ATTACK;
		if(!getline(ss,destination,' '))
			throw BadInputException("no destination has been entered");
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		break;
	case 7:
		shipCMD = REFUEL;
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		break;
	case 8:
		shipCMD = STOP;
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra chars in input");
		break;
	default:
		throw BadInputException("command does not exist");
	}
}





void CommandInfo::createConditions(string line){

	stringstream ss(line);
	string buffer;
	int argCounter=0,tempArg;
	while(getline(ss,buffer,' ')){
		argCounter++;
		switch (argCounter) {
		case 1:
			shipName = buffer;
			break;

		case 2:
			setShipType(buffer);
			break;

		case 3:
			getXCoordinate(buffer,arg1);	// get the x coordiante
			break;
		case 4:
			getYCoordinate(buffer,arg2);// get the y coordiante
			if(type == Ship::Type::CRUISE_SHIP){
				char garbage;
				ss >> garbage;
				if(!ss.fail())
					throw BadInputException("extra chars in input");
			}
			break;
		case 5:
			if(type == Ship::Type::CRUISE_SHIP)
				throw BadInputException("cruise ship needs only 4 arguments");
			getInt(buffer,tempArg); // get maxCargo/force
			arg3 = tempArg;
			break;
		case 6:
			if(type == Ship::Type::CRUISE_SHIP)
				throw BadInputException("cruise ship needs only 4 arguments");
			getInt(buffer,tempArg);	// get resistance/range
			char garbage;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra chars in input");
			arg4 = tempArg;
			break;
		default:
			throw BadInputException("too much arguments have been entered for create command");
		}
	}
}


// determine ship type
void CommandInfo::setShipType(string buffer){
	array<string,3> shipTypes = {"Freighter","Cruise_ship","Cruiser"};

	if(buffer == shipTypes[0])
		type = Ship::Type::FREIGHTER;
	else if(buffer == shipTypes[1])
		type = Ship::Type::CRUISE_SHIP;
	else if(buffer == shipTypes[2])
		type = Ship::Type::CRUISER;
	else{
		throw BadInputException((buffer + " is an illegal ship type on create").c_str());
	}

}




// return true if succeed
void CommandInfo::getXCoordinate(string buffer,double& arg){
	stringstream ss(buffer);
	string tempBuff;
	char garbage;

	ss >> garbage;
	if(garbage != '('){
		throw BadInputException("the x coordinate is bad");
	}

	ss >> arg;
	if(ss.fail())
		throw BadInputException("double as not been entered properly");
	ss >> garbage;
	if(!ss.fail())
		if(garbage != ',')
			throw BadInputException("no , between coordinates");
	ss >> garbage;
	if(!ss.fail())
		throw BadInputException("extra chars in input");

}


void CommandInfo::getYCoordinate(string buffer,double& arg){
	stringstream ss(buffer);
	string tempBuff;
	char garbage;

	ss >> arg;
	if(ss.fail())
		throw BadInputException("double as not been entered properly");
	ss >> garbage;
	if(garbage != ')')
		throw BadInputException("coordinates does not end with )");
	ss >> garbage;
	if(!ss.fail())
		throw BadInputException("extra chars in input");

}

// try to read an int or a double from the input
void CommandInfo::getIntOrDouble(string buffer,double& arg){
	try {
		int tempArg;
		getInt(buffer,tempArg);
		arg = tempArg;
	} catch (BadInputException& e) {
		getDouble(buffer,arg);
	}
}

// get int safely from input
void CommandInfo::getInt(string buffer,int& arg){
	stringstream ss(buffer);
	int temp;
	char garbage;

	ss >> temp;
	if(ss.fail())
		throw BadInputException("int as not been entered properly");
	ss >> garbage;
	if(!ss.fail())
		throw BadInputException("extra chars in input");
	arg = temp;
}

// get double safely from input
void CommandInfo::getDouble(string buffer,double& arg){
	stringstream ss(buffer);
	double temp;
	char garbage;

	ss >> temp;
	if(ss.fail())
		throw BadInputException("double as not been entered properly");
	ss >> garbage;
	if(!ss.fail())
		throw BadInputException("extra chars in input");
	arg = temp;
}



