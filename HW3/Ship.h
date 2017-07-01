/*
 * Ship.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "MarineElement.h"
#include "Scouter.h"
#include <string>
#include <queue>
#include <memory>

class Ships_commands;


using std::string;
using std::queue;
using std::shared_ptr;



class Ship: public Marine_Element {
    
private:
    
    double arg;
    double velocity;
    queue<shared_ptr<Ships_commands>> command_queue;
    
    
    
    enum State {STOPPED, DOCKED, DEAD, MOVING}; // current state;

    
    State state;
    Scouter scouter;
    
public:
    enum Type {FREIGHTER, CRUISE_SHIP, CRUISER };   //Neccessary for ship creation.

	Ship();
	virtual ~Ship();
    
    
    void halt();
    virtual void go()=0;
    virtual void enqueue(Ships_commands *sc);
    
    virtual void dock(string pname); //Cruiser not allowed to dock.
    virtual void refuel();           //same, cruiser doesnt need to refuel.
    void set_destination(int x,int y);
    void set_destination(string port_name);
    void set_direction(double arg);
    void set_velocity(double v);
    
    
    
    virtual void status()const = 0;
    
    

    
};

#endif /* SHIP_H_ */
