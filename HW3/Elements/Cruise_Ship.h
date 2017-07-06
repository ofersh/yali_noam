
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
    vector<weak_ptr<Port>> remainingPorts;
    
    bool waiting_for_action;
    
    constexpr static const double MAXFUEL = 900;        // maximum fuel
    constexpr static const double MAXVELOCITY = 15;     // maximum velocity
    constexpr static const double LPM = 2;              // liter per mile (fuel consumption)
    
    void findNextPort();    //find next clost port.
    
public:
    Cruise_Ship(string name, Point pos);
    ~Cruise_Ship();
    
    void go(); //perform a step.
    void status()const; //print status of ship.
    Ship::Type getType()const;   //return type.
    
    
    bool under_attack(Cruiser * attacking); //double dispatch method.

};

#endif /* CRUISE_SHIP_H_ */
