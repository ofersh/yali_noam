/*
 * CommandInfo.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_COMMANDINFO_H_
#define UTILITIES_COMMANDINFO_H_

#include <string>

using std::string;


class CommandInfo {
public:
	CommandInfo()=default;
	virtual ~CommandInfo()=default;
	enum CommandSection{MODEL,VIEW,SHIP,QUIT};
	enum Commands{STATUS,GO,CREATE,DEFAULT,SIZE,ZOOM,PAN,SHOW};
	enum shipCommand{COURSE,POSITION,DESTINATION,LOAD_AT,UNLOAD_AT,DOCK_AT,ATTACK,REFUEL,STOP};


	bool breakCommand(string buffer);
	static bool getCoordinate(string buffer,int& arg,char c);
	static bool getInt(string buffer,int& arg);
	string shipName,destination;
	Ship::Type type;
	Commands cmd;
	shipCommand shipCMD;
	CommandSection cmdSec;
	double arg1,arg2,arg3,arg4;


private:
	bool shipCommand(string line);

	bool createConditions(string line);
};

#endif /* UTILITIES_COMMANDINFO_H_ */
