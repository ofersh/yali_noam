/*
 * Freighter.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef FREIGHTER_H_
#define FREIGHTER_H_

#include "Ship.h"
#include <memory>


class Port;
using std::weak_ptr;


class Freighter: public Ship {
    
private:
    unsigned int container;
    unsigned int maxCargo;
    int resistence;
    weak_ptr<Port> destinationPort;
   
    
    constexpr static const double MAXFUEL = 500;        // maximum fuel
    constexpr static const double MAXVELOCITY = 40;     // maximum velocity
    constexpr static const double LPM = 1;              // liter per mile (fuel consumption)

    
public:
    Freighter(int maxCont, int res,Ship::Type t, string name, int x, int y, double fuel);
    ~Freighter();
    
    
    void dock(weak_ptr<Port> portName);
    void refuel();
    void setDestination(weak_ptr<Port> portName);
    void disembark(weak_ptr<Port> portName, int amount);   //unload_at
    void embark(weak_ptr<Port> portName);  //load_at
    void fuel();
     
    void status()const;
};

#endif /* FREIGHTER_H_ */
