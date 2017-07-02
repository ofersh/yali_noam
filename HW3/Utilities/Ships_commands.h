//
//  ships_commands.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Utilities_Ships_commands_h
#define Utilities_Ships_commands_h

#include "../Elements/Ship.h"



/** thinking about functor Family for each ship functionality*/

class Ships_commands {
    
public:
    Ships_commands();
    virtual ~Ships_commands();
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


//Stop Functor.
class Stop :public Ships_commands
{
public:
    void operator()(Ship * s){
        s->halt();
    };
};





#endif /* ships_commands_hpp */
