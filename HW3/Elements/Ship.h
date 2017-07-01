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
    
public:
    enum State {STOPPED, DOCKED, DEAD, MOVING}; // current state.

private:
    State state;

    queue<shared_ptr<Ships_commands>> command_queue;   //command queue.
    Scouter scouter;

    
public:
    enum Type {FREIGHTER, CRUISE_SHIP, CRUISER };   //Neccessary for ship creation.

	Ship(Type t, string name, int x, int y, double fuel);
	virtual ~Ship();
    
    virtual void go()=0;
    virtual void enqueue(Ships_commands *sc);   //V
    
    void halt();    //V
    void set_direction(double arg);
    void set_velocity(double v);
    void set_state(State state);
    State get_state()const {return state;};
    virtual void status()const = 0;
    double calculate_distance(coordinates to);
    void calculate_route();
    

    
};

#endif /* SHIP_H_ */
