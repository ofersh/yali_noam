/*
 * Freighter.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef FREIGHTER_H_
#define FREIGHTER_H_

#include "Civil_ship.h"
#include <memory>

class Freighter: public Civil_ship {
    
private:
    unsigned int current_containers;
    unsigned int maxCargo;
    int resistence;   
    
    constexpr static const double MAXFUEL = 500;        // maximum fuel
    constexpr static const double MAXVELOCITY = 40;     // maximum velocity
    constexpr static const double LPM = 1;              // liter per mile (fuel consumption)

    
public:
    Freighter(unsigned int maxCont, int res,Ship::Type t, string name, int x, int y, double fuel, weak_ptr<Port> dest_port);
    ~Freighter();
    
    
    void disembark(weak_ptr<Port> port,unsigned int amount);   //unload_at
    void embark(weak_ptr<Port> port);  //load_at
    unsigned int containers_amount()const {return current_containers;};
    unsigned int empty_space()const{return maxCargo-current_containers;};
    void add_cargo(unsigned int amount);

    void status()const;
};

#endif /* FREIGHTER_H_ */
