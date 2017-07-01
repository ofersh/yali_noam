/*
 * Ship.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "MarineElement.h"
#include "Port.h"
#include "../Utilities/Scouter.h"
#include <string>
#include <queue>
#include <memory>

class Ships_commands;


using std::string;
using std::queue;
using std::shared_ptr;
using std::weak_ptr;


class Ship: public Marine_Element {
    
private:
    
    queue<shared_ptr<Ships_commands>> command_queue;   //command queue.
    
    enum State {STOPPED, DOCKED, DEAD, MOVING}; // current state.

    State state;
    Scouter scouter;
    weak_ptr<Port> destination;
    
    void calculate_route();
    
public:
    enum Type {FREIGHTER, CRUISE_SHIP, CRUISER };   //Neccessary for ship creation.

	Ship(Type t, string name, int x, int y, double fuel);
	virtual ~Ship();
    
    virtual void go()=0;
    virtual void enqueue(Ships_commands *sc);   //V
    
    void halt();    //V
    void set_direction(double arg);
    void set_velocity(double v);
    
    virtual void status()const = 0;

    
};

#endif /* SHIP_H_ */
