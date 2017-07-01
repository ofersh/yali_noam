/*
 * CivilShipsCommands.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_CIVILSHIPSCOMMANDS_H_
#define UTILITIES_CIVILSHIPSCOMMANDS_H_

#include "Ships_commands.h"

class Civil_Ships_Commands: public Ships_commands {
public:
	Civil_Ships_Commands();
	virtual ~Civil_Ships_Commands();

	virtual void operator()(Ship *)=0;
};

class Destination :public Civil_Ships_Commands
{
private:
    string port_name;
    double velocity;

public:
    Destination(string port_name, double v);
    ~Destination();

    void operator()(Ship *s){
        s->set_destination(port_name);
        s->set_velocity(velocity);
    }
};


//Dock Functor.
class Dock_at :public Civil_Ships_Commands
{
private:
    string port_name;
public:
    Dock_at(string pname);
    ~Dock_at();

    void operator()(Ship * s){
        s->dock(port_name);
    }
};


//Refuel functor.
class Refuel :public Civil_Ships_Commands
{

public:
    void operator()(Ship * s){
        s->refuel();
    };
};

#endif /* UTILITIES_CIVILSHIPSCOMMANDS_H_ */
