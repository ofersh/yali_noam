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
		checkForExtraChars(ss);
		return;
	case 1:
		cmdSec = CommandSection::MODEL;
		cmd = Commands::GO;
		checkForExtraChars(ss);
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
		checkForExtraChars(ss);
		return;
	case 4:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SIZE;
		// check validity of size command
		getline(ss,buffer,' ');
		getInt(buffer,tempArg);
		switch (static_cast<unsigned int>(tempArg)) {
			case 0-6:
				throw BadInputException("New map size is too small");
			case tempArg > 30:
				throw BadInputException("New map size is too big");
			default:
				break;
		}
		checkForExtraChars(ss);
		return;

	case 5:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::ZOOM;
		// check validity of zoom command
		getline(ss,buffer,' ');
		try{getInt(buffer,tempArg);
		checkForExtraChars(ss);
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
		checkForExtraChars(ss);
		arg2 = tempArg;
		return;

	case 7:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SHOW;
		checkForExtraChars(ss);
		return ;
	case 8:
		cmdSec = CommandSection::QUIT;
		checkForExtraChars(ss);
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
			checkForExtraChars(ss);
			return;

		case 1:
			shipCMD = POSITION;
			getline(ss,buffer,' ');
			getXCoordinate(buffer,arg1);		// get x
			getline(ss,buffer,' ');
			getYCoordinate(buffer,arg2);		// get y
			getline(ss,buffer,' ');
			getDouble(buffer,arg3);				// get velocity
			checkForExtraChars(ss);
			return;

		case 2:
			shipCMD = DESTINATION;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			getline(ss,buffer,' ');
			getInt(buffer,tempArg);
			checkForExtraChars(ss);
			arg1 = tempArg;
			break;

		case 3:
			shipCMD = LOAD_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			checkForExtraChars(ss);
			break;

		case 4:
			shipCMD = UNLOAD_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			getline(ss,buffer,' ');
			getInt(buffer,tempArg);
			checkForExtraChars(ss);
			arg1 = tempArg;
			break;

		case 5:
			shipCMD = DOCK_AT;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			checkForExtraChars(ss);
			break;
		case 6:
			shipCMD = ATTACK;
			if(!getline(ss,destination,' '))
				throw BadInputException("no destination has been entered");
			checkForExtraChars(ss);
			break;
		case 7:
			shipCMD = REFUEL;
			checkForExtraChars(ss);
			break;
		case 8:
			shipCMD = STOP;
			checkForExtraChars(ss);
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
				checkForExtraChars(ss);
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
	checkForExtraChars(ss);

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
	checkForExtraChars(ss);

}



void CommandInfo::getInt(string buffer,int& arg){
	stringstream ss(buffer);
	int temp;
	char garbage;

	ss >> temp;
	if(ss.fail())
		throw BadInputException("int as not been entered properly");
	checkForExtraChars(ss);
	arg = temp;
}


void CommandInfo::getDouble(string buffer,double& arg){
	stringstream ss(buffer);
	double temp;
	char garbage;

	ss >> temp;
	if(ss.fail())
		throw BadInputException("double as not been entered properly");
	checkForExtraChars(ss);
	arg = temp;
}

void CommandInfo::checkForExtraChars(stringstream& ss){
	char garbage;
	ss >> garbage;
	if(!ss.fail())
		throw BadInputException("extra chars in input");
}

