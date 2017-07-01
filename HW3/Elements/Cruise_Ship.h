/*
 * CruiseShip.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef CRUISE_SHIP_H_
#define CRUISE_SHIP_H_

#include "Ship.h"
#include <memory>
#include <vector>


class Port;
using std::weak_ptr;
using std::vector;

class Cruise_Ship: public Ship {

private:
    int resistence;
    weak_ptr<Port> currentPort;
    vector<weak_ptr<Port>> remainingPorts;
    
    
    constexpr static const double MAXFUEL = 900;        // maximum fuel
    constexpr static const double MAXVELOCITY = 15;     // maximum velocity
    constexpr static const double LPM = 2;              // liter per mile (fuel consumption)
    
    
    void findNextPort();
    
    
    
public:
    Cruise_Ship();
    virtual ~Cruise_Ship();
    
    
    void dock(string pname);
    void refuel();

    void setDestination(string portName);
    void dock();
    void fuel();
    
    void status()const;


};

#endif /* CRUISE_SHIP_H_ */
