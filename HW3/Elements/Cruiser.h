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

using std::weak_ptr;

class Freighter;
class CruiseShip;


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
    void attack();  //commence attack.
    
    
    /** maybe double disptach ??? */
    void attack(Freighter *);   //attacking Freighter
    void attack(CruiseShip *);  //attacking Cruise.
};

#endif /* CRUISER_H_ */
