//
//  Civil_ship.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef ELEMENTS_Civil_ship_hpp
#define ELEMENTS_Civil_ship_hpp

#include "Ship.h"
#include <stdio.h>

class Civil_Ships_Commands;
class Port;

class Civil_ship :public Ship {

private:
    constexpr static const double DOCKING_RANGE=0.1;

    bool fuelling;
    weak_ptr<Port> destination;
    
public:
    Civil_ship(Type t, string name, Point pos, double fuel, double lpm);
    virtual ~Civil_ship()=0;
    
    
    bool dock(weak_ptr<Port> port); // try dock at given port.
    void setDestination(weak_ptr<Port> port);   //set destination to port.
    bool refuel();  //try to refuel.
    void set_Waiting_for_fuel(bool b); //for fuel flag.
    bool isFuelling()const{return fuelling;};
    weak_ptr<Port> get_destination()const{return destination;};
    
    void enqueue(Civil_Ships_Commands *csc ); //enqueue new command.
};

#endif /* Civil_ship_hpp */
