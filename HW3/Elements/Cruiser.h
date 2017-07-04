/*
 * PirateShip.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef ELEMENTS_CRUISER_H_
#define ELEMENTS_CRUISER_H_

#include "Ship.h"
#include <memory>
class Civil_ship;


using std::weak_ptr;

class Freighter;
class Cruise_Ship;


class Cruiser: public Ship {
    
    
private:
    
    int force;
    double range;
    
    
    constexpr static const double MAXVELOCITY = 75;     // maximum velocity

     weak_ptr<Ship> find_target(); //find next target in range.
    
    
public:
	Cruiser(Type t, string name, Point pos , int force, double range);
	virtual ~Cruiser();
    
    
    void status()const;
    bool attack(weak_ptr<Civil_ship> target);  //commence attack.
    bool attack(Freighter * fr);
    bool attack(Cruise_Ship * cs);
    
    Ship::Type getType();
};

#endif /* CRUISER_H_ */
