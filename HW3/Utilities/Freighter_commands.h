//
//  Freighter_commands.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Freighter_commands_h
#define Freighter_commands_h

#include "CivilShipsCommands.h"
#include "../Elements/Freighter.h"


//Freighter only commands.
class Freighter_commands :public Civil_Ships_Commands {
public:
    
    void operator()(Freighter * f);
};


//Load Functor.
class Load_at :public Freighter_commands {
    
    string port_name;
    
public:
    Load_at(string pname);
    
    void operator()(Freighter * f){
        f->embark(port_name);
    };

    void operator()(Ship* f){
    	operator ()(dynamic_cast<Freighter*>(f));
    };
};


//Unload Functor.
class Unload_at :public Freighter_commands {
    
    string port_name;
    int amount;
    
public:
    Unload_at(string pname, int amount);
    
    void operator()(Freighter * f){
        f->disembark(port_name, amount);
    };
    void operator()(Ship* f){
        	operator ()(dynamic_cast<Freighter*>(f));
        };
};







#endif /* Freighter_commands_hpp */
