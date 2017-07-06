
#ifndef Utilities_Freighter_commands_h
#define Utilities_Freighter_commands_h

#include "CivilShipsCommands.h"
#include "../Elements/Freighter.h"


//Freighter only commands.
class Freighter_commands :public Civil_Ships_Commands {
public:
    
    virtual bool operator()(Freighter * f)=0;
    virtual bool operator()(Civil_ship * cs){return operator()(dynamic_cast<Freighter*>(cs));};
};


//Load Functor.
class Load_at :public Freighter_commands {
    
	weak_ptr<Port> port_name;
    
public:
    Load_at(weak_ptr<Port> port):port_name(port){}
    
    bool operator()(Freighter * f){
        return f->embark(port_name);
    };
};


//Unload Functor.
class Unload_at :public Freighter_commands {
    
	weak_ptr<Port> port;
    int amount;
    
public:
    Unload_at(weak_ptr<Port> port, int amount):port(port),amount(amount){}
    
    bool operator()(Freighter * f){
        return f->disembark(port, amount);
    };

};







#endif /* Freighter_commands_hpp */
