/*
 * PirateShip.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef PIRATESHIP_H_
#define PIRATESHIP_H_

#include "Ship.h"
#include <memory>

using std::weak_ptr;

class Freighter;
class CruiseShip;


class Pirate_Ship: public Ship {
    
    
private:
    
    int force;
    double range;
    
    
    constexpr static const double MAXVELOCITY = 75;     // maximum velocity

     weak_ptr<Ship> find_target(); //find next target in range.
    
    
public:
	Pirate_Ship();
	virtual ~Pirate_Ship();
    
    
    void status()const;
    void attack();  //commence attack.
    
    
    /** maybe double disptach ??? */
    void attack(Freighter *);   //attacking Freighter
    void attack(CruiseShip *);  //attacking Cruise.
};

#endif /* PIRATESHIP_H_ */
