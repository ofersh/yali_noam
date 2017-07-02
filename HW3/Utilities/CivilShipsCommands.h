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

class Civil_Ships_Commands: public Ships_commands {
public:
	Civil_Ships_Commands();
	virtual ~Civil_Ships_Commands();

    bool operator()(Ship*){};
	virtual bool operator()(Civil_ship *s)=0;
};

class Destination :public Civil_Ships_Commands
{
private:
    weak_ptr<Port> port_name;
    double velocity;

public:
    Destination(weak_ptr<Port> port_name, double v):port_name(port_name),velocity(v){};
    ~Destination();

    bool operator()(Civil_ship *s){
        s->setDestination(port_name);
        s->set_velocity(velocity);
        return true;
    }
};


//Dock Functor.
class Dock_at :public Civil_Ships_Commands
{
private:
	weak_ptr<Port> port;
public:
    Dock_at(weak_ptr<Port> p):port{p}{
    };
    ~Dock_at(){};

    bool operator()(Civil_ship * s){
        return s->dock(port);
    }
};


//Refuel functor.
class Refuel :public Civil_Ships_Commands
{

public:
    bool operator()(Civil_ship * s){
        return s->refuel();
        
    };
};

#endif /* UTILITIES_CIVILSHIPSCOMMANDS_H_ */
