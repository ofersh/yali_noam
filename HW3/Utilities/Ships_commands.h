

#ifndef Utilities_Ships_commands_h
#define Utilities_Ships_commands_h

#include "../Elements/Ship.h"



/** thinking about functor Family for each ship functionality*/

class Ships_commands {
    
public:
    Ships_commands()=default;
    virtual ~Ships_commands()=default;
    virtual bool operator()(Ship *)=0;

};

//general functors, for all ships.
//course functor.
class Course :public Ships_commands
{
private:
    double arg;
    double velocity;
    
public:
    Course(double arg, double v):arg(arg),velocity(v){};
    ~Course()=default;
    
    bool operator()(Ship * s){
        s->set_direction(arg);
        s->set_velocity(velocity);
        s->set_no_destination();
        s->set_state(Ship::State::MOVING);
        return true; //allways succseed
    };
};


//position functor.
class Positon :public Ships_commands
{
private:
    int x,y;
    double velocity;
    
public:
    Positon(int x, int y, double v):x(x),y(y),velocity(v){};
    ~Positon()=default;
    
    bool operator()(Ship * s){
        s->set_velocity(velocity);
        s->setPosition(x,y);
        return true;
    };
};

//destination functor.


//Stop Functor.
class Stop :public Ships_commands
{
public:
    bool operator()(Ship * s){
        s->halt();
        return true;
    };
};





#endif /* ships_commands_hpp */
