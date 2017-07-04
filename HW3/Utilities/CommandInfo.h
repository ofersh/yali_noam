/*
 * CommandInfo.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_COMMANDINFO_H_
#define UTILITIES_COMMANDINFO_H_

#include <string>
#include "Ship.h"

using std::string;


class CommandInfo {
public:



	enum CommandSection{MODEL=0,VIEW=1,SHIP=2,QUIT=3};
	enum Commands{STATUS=0,GO=1,CREATE=2,DEFAULT=3,SIZE=4,ZOOM=5,PAN=6,SHOW=7};
	enum shipCommand{COURSE=0,POSITION=1,DESTINATION=2,LOAD_AT=3,UNLOAD_AT=4,DOCK_AT=5,ATTACK=6,REFUEL=7,STOP=8};

	void breakCommand(string buffer);


	static void getXCoordinate(string buffer,double& arg);
	static void getYCoordinate(string buffer,double& arg);
	static void getInt(string buffer,int& arg);
	static void getDouble(string buffer,double& arg);


	string shipName,destination;
	Ship::Type type;
	Commands cmd;
	shipCommand shipCMD;
	CommandSection cmdSec;
	double arg1,arg2,arg3,arg4;


private:
	void shipCommandBreak(string line);
	void setShipType(string type);
	void createConditions(string line);
};

#endif /* UTILITIES_COMMANDINFO_H_ */
