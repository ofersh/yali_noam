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

using std::string;

class Ship: public Marine_Element {
    
private:
    enum State {STOPPED, DOCKED, DEAD, MOVING}; // current state;

    
    State state;
    Scouter scouter;
    
public:
    enum Type {FREIGHTER, CRUISE_SHIP, CRUISER };   //Neccessary for ship creation.

	Ship();
	virtual ~Ship();
    
    
    void halt();
    virtual void dock();
    void set_destination(int x,int y);
    void set_direction(double arg);
    
    virtual void status()const = 0;
    
    

    
};

#endif /* SHIP_H_ */
