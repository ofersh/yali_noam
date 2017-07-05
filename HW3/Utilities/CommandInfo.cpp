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
		// check validity of status command
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra characters on status command");
		return;
	case 1:
		cmdSec = CommandSection::MODEL;
		cmd = Commands::GO;
		// check validity of go command
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra characters on go command");
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
		// check validity of default command
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra characters on default command");
		return;
	case 4:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SIZE;
		// check validity of size command
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg1 = tempArg;
		return;

	case 5:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::ZOOM;
		// check validity of zoom command
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg1 = tempArg;
		return;

	case 6:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::PAN;
		// check validity of pan command
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg1 = tempArg;
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		arg2 = tempArg;
		return;

	case 7:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SHOW;
		// check validity of show command
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra characters on show command");;
		return ;
	case 8:
		cmdSec = CommandSection::QUIT;
		// check validity of quit command
		ss >> garbage;
		if(!ss.fail())
			throw BadInputException("extra characters on quit command");
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
			return;

		case 1:
			shipCMD = POSITION;
			getline(ss,buffer,' ');
			getXCoordinate(buffer,arg1);		// get x
			getline(ss,buffer,' ');
			getYCoordinate(buffer,arg2);		// get y
			getline(ss,buffer,' ');
			getDouble(buffer,arg3);				// get velocity
			return;

		case 2:
			shipCMD = DESTINATION;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			getline(ss,buffer,' ');
			getInt(buffer,tempArg);
			arg1 = tempArg;
			break;

		case 3:
			shipCMD = LOAD_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra characters in LOAD_AT");
			break;

		case 4:
			shipCMD = UNLOAD_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			getline(ss,buffer,' ');
			getInt(buffer,tempArg);
			arg1 = tempArg;
			break;

		case 5:
			shipCMD = DOCK_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra characters in DOCK_AT");
			break;
		case 6:
			shipCMD = ATTACK;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra characters in ATTACK");
			break;
		case 7:
			shipCMD = REFUEL;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra characters in command refuel");
			break;
		case 8:
			shipCMD = STOP;
			ss >> garbage;
			if(!ss.fail())
				throw BadInputException("extra characters in command STOP");
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
				arg4 = tempArg;
				break;
			default:
				throw BadInputException("too much arguments have been entered for create command");
		}
	}
}



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
	if(garbage != '('){//create Ajax Cruiser (15.00 15.00) 6 1{
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
		throw BadInputException("extra characters in x coordinate");


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
		throw BadInputException("extra characters in x coordinate");


}



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
