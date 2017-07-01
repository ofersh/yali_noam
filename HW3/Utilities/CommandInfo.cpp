/*
 * CommandInfo.cpp
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#include "CommandInfo.h"
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool CommandInfo::breakCommand(string line){
	vector<string> mvCMD = {"status","go","create","default","size","zoom","pan","show","quit"};
	stringstream ss(line);
	string buffer;
	int tempArg;
	char garbage;


	ss >> buffer;
	auto pos = find(mvCMD.begin(),mvCMD.end(),buffer) - mvCMD.begin();
	switch (pos) {
	case 0:
		cmdSec = CommandSection::MODEL;
		cmd = Commands::STATUS;
		// check validity of status command
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;
	case 1:
		cmdSec = CommandSection::MODEL;
		cmd = Commands::GO;
		// check validity of go command
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;
	case 2:
		cmdSec = CommandSection::MODEL;
		cmd = Commands::CREATE;
		// check validity of create command
		getline(ss,buffer);
		return createConditions(buffer);
	case 3:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::DEFAULT;
		// check validity of default command
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;
	case 4:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SIZE;
		// check validity of size command
		ss >> tempArg;
		if(ss.fail())
			return false;
		ss >> garbage;
		if(!ss.fail())
			return false;
		arg1 = tempArg;
		return true;

	case 5:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::ZOOM;
		// check validity of zoom command
		ss >> arg1;
		if(ss.fail())
			return false;
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;

	case 6:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::PAN;
		// check validity of pan command
		ss >> arg1;
		if(ss.fail())
			return false;
		ss >> arg2;
		if(ss.fail())
			return false;
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;

	case 7:
		cmdSec = CommandSection::VIEW;
		cmd = Commands::SHOW;
		// check validity of show command
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;
	case 8:
		cmdSec = CommandSection::QUIT;
		// check validity of quit command
		ss >> garbage;
		if(!ss.fail())
			return false;
		return true;
	default:
		cmdSec = CommandSection::SHIP;
		break;
	}
	shipName = buffer;
	// get the rest of the text
	getline(ss,buffer);
	return shipCommand(buffer);
}


bool CommandInfo::shipCommand(string line){
	vector<string> shipCMD = {"course","position","destination","load_at","unload_at","dock_at","attack","refuel","stop"};
	stringstream ss(line);
	string buffer;
	int tempArg;
	char garbage;

	ss >> buffer;
	auto pos = find(shipCMD.begin(),shipCMD.end(),buffer) - shipCMD.begin();
	switch (pos) {
		case 0:
			shipCMD = COURSE;
			ss >> arg1;
			if(ss.fail())
				return false;
			ss >> arg2;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;

		case 1:
			shipCMD = POSITION;

			ss >> buffer;
			if(ss.fail())
				return false;
			if(!getCoordinate(buffer,tempArg,'('))
				return false;
			arg1 = tempArg;
			ss >> buffer;
			if(!getCoordinate(buffer,tempArg,')'))
				return false;
			arg2 = tempArg;
			ss >> arg3;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;

		case 2:
			shipCMD = DESTINATION;
			ss >> destination;
			if(ss.fail())
				return false;
			ss >> arg1;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;

		case 3:
			shipCMD = LOAD_AT;
			ss >> destination;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;

		case 4:
			shipCMD = UNLOAD_AT;
			ss >> destination;
			if(ss.fail())
				return false;
			ss >> arg1;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;

		case 5:
			shipCMD = DOCK_AT;
			ss >> destination;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;
		case 6:
			shipCMD = ATTACK;
			ss >> destination;
			if(ss.fail())
				return false;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;
		case 7:
			shipCMD = REFUEL;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;
		case 8:
			shipCMD = STOP;
			ss >> garbage;
			if(!ss.fail())
				return false;
			break;
		default:
			break;
	}
	return true;
}

// return true if succeed
bool CommandInfo::getCoordinate(string buffer,int& arg,char c){
	stringstream ss(buffer);
	string tempBuff;
	int pos;
	char garbage;

	ss >> garbage;
	if(garbage != c)
		return false;

	getline(ss,tempBuff);
	return getInt(tempBuff,arg);
}

bool getInt(string buffer,int& arg){
	stringstream ss(buffer);
		int pos;
		char garbage;

		ss >> pos;
		if(ss.fail())
			return false;
		ss >> garbage;
		if(!ss.fail())
			return false;
		arg = pos;
		return true;
}

int getShipType(string type){
	int numberOfShipTypes = 3,notExist=-1;
	array<string,numberOfShipTypes> shipTypes = {"Freighter","Cruise_ship","Cruiser"};
	for (int i = 0; i < numberOfShipTypes; ++i) {
		if(type == shipTypes[i])
			return i;
	}
	return notExist;
}


bool CommandInfo::createConditions(string line){

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
				switch (getShipType(buffer)) {
					case 0:
						type = Ship::Type::FREIGHTER;
						break;
					case 1:
						type = Ship::Type::CRUISE_SHIP;
						break;
					case 2:
						type = Ship::Type::CRUISER;
						break;
					default:
						return false;
				}
				break;

			case 3:
				if(!getCoordinate(buffer,tempArg,'('))
					return false;
				arg1 = tempArg;
				break;
			case 4:
				if(!getCoordinate(buffer,tempArg,')'))
					return false;
				arg2 = tempArg;
				break;
			case 5:
				if(type == Ship::Type::CRUISE_SHIP)
					return false;
				if(!getInt(buffer,tempArg))
					return false;
				arg3 = tempArg;
				break;
			case 6:
				if(type == Ship::Type::CRUISE_SHIP)
					return false;
				if(!getInt(buffer,tempArg))
					return false;
				arg3 = tempArg;
				break;
			default:
				return false;
		}
	}



	return true;
}
