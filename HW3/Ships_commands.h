//
//  ships_commands.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Ships_commands_h
#define Ships_commands_h

#include <stdio.h>
#include "Ship.h"



/** thinking about functor Family for each ship functionality*/

class Ships_commands {
    
public:
    Ships_commands();
    ~Ships_commands();
    virtual void operator()(Ship *)=0;
    
};

//general functors, for all ships.
//course functor.
class Course :public Ships_commands
{
private:
    double arg;
    double velocity;
    
public:
    Course(double arg, double v);
    ~Course();
    
    void operator()(Ship * s){
        s->set_direction(arg);
        s->set_velocity(velocity);
    };
};

//position functor.
class Positon :public Ships_commands
{
private:
    int x,y;
    double velocity;
    
public:
    Positon(int x, int y, double v);
    ~Positon();
    
    void operator()(Ship * s){
        s->set_velocity(velocity);
        s->setPosition(x,y);
    };
};

//destination functor.
class Destination :public Ships_commands
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
class Dock_at :public Ships_commands
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
class Refuel :public Ships_commands
{
    
public:
    void operator()(Ship * s){
        s->refuel();
    };
};

//Stop Functor.
class Stop :public Ships_commands
{
public:
    void operator()(Ship * s){
        s->halt();
    };
};





#endif /* ships_commands_hpp */
