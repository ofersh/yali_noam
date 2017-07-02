/*
 * CruiseShip.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef ELEMENTS_CRUISE_SHIP_H_
#define ELEMENTS_CRUISE_SHIP_H_

#include "Civil_ship.h"
#include <memory>
#include <vector>


class Port;
using std::weak_ptr;
using std::vector;

class Cruise_Ship: public Civil_ship {

private:
    int resistence;
    vector<weak_ptr<Port>> remainingPorts;
    
    bool waiting_for_action;
    
    constexpr static const double MAXFUEL = 900;        // maximum fuel
    constexpr static const double MAXVELOCITY = 15;     // maximum velocity
    constexpr static const double LPM = 2;              // liter per mile (fuel consumption)
    
    void findNextPort();
    
    
    
public:
    Cruise_Ship(Type t, string name, coordinates pos, double fuel);
    ~Cruise_Ship();
    
    void go();
    void status()const;
};

#endif /* CRUISE_SHIP_H_ */
