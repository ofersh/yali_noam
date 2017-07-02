/*
 * Ship.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef ELEMENTS_SHIP_H_
#define ELEMENTS_SHIP_H_

#include "MarineElement.h"
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
    double fuel_consumption;
    queue<shared_ptr<Ships_commands>> command_queue;   //command queue.
    Scouter scouter;

    
public:
    enum Type {FREIGHTER, CRUISE_SHIP, CRUISER };   //Neccessary for ship creation.

	Ship(Type t, string name,Point position, double fuel, double fuel_consumption);
	virtual ~Ship();
    
    virtual void enqueue(Ships_commands *sc);
    
    void halt();
    void advance(); //actual moving functin, needs to calculate progress and LPM
    void set_direction(double arg);
    void set_velocity(double v);
    void set_state(State state);
    
    State get_state()const {return state;};
    
    
    shared_ptr<Ships_commands> getNextCommand()const;
    void dequeue_command();
    
    
    //get info from scouter.
    double getAzimuth()const{return scouter.getAzimuth();};
    double getVelocity()const{return scouter.getVelocity();};
    Point getDestCoordinates(){return scouter.getDestCoordinates();};

    double calculate_distance(Point to);
    void calculate_route();
    

    
};

#endif /* SHIP_H_ */
