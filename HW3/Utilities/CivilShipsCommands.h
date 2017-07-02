/*
 * CivilShipsCommands.h
 *
 *  Created on: 1 Jul 2017
 *      Author: noam
 */

#ifndef UTILITIES_CIVILSHIPSCOMMANDS_H_
#define UTILITIES_CIVILSHIPSCOMMANDS_H_

#include "Ships_commands.h"
#include "../Elements/Civil_ship.h"

//#include "../Elements/Civil_ship.h"

class Civil_Ships_Commands: public Ships_commands {
public:
	Civil_Ships_Commands();
	virtual ~Civil_Ships_Commands();

	virtual void operator()(Civil_Ship *s)=0;
};

class Destination :public Civil_Ships_Commands
{
private:
    weak_ptr<Port> port_name;
    double velocity;

public:
    Destination(weak_ptr<Port> port_name, double v):port_name(port_name),velocity(v){};
    ~Destination();

    void operator()(Civil_Ship *s){
        s->set_destination(port_name);
        s->set_velocity(velocity);
    }
};


//Dock Functor.
class Dock_at :public Civil_Ships_Commands
{
private:
	weak_ptr<Port> port_name;
public:
    Dock_at(weak_ptr<Port> port_name);
    ~Dock_at();

    void operator()(Civil_Ship * s){
        s->dock(port_name);
    }
};


//Refuel functor.
class Refuel :public Civil_Ships_Commands
{

public:
    void operator()(Civil_Ship * s){
        s->refuel();
    };
};

#endif /* UTILITIES_CIVILSHIPSCOMMANDS_H_ */
