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
    class Course;
    Ships_commands();
    virtual ~Ships_commands()=0;
    virtual void operator()()=0;

};

//general functors, for all ships.
class Ships_commands::Course :public Ships_commands
{
private:
    double arg;
    double velocity;
    
public:
    void operator()(Ship * s){
        
    };
    
};

class Positon :public Ships_commands
{
    
};


class Destination :public Ships_commands
{
    
};

class Dock_at :public Ships_commands
{
    
};


class Refuel :public Ships_commands
{
    
};

class Stop :public Ships_commands
{
    
};





#endif /* ships_commands_hpp */
