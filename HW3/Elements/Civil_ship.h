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
#include "../Utilities/CivilShipsCommands.h"
#include <stdio.h>

class Port;

class Civil_ship :public Ship {

private:
    constexpr static const double DOCKING_RANGE=0.1;

    bool fuelling;
    weak_ptr<Port> destination;
    
public:
    Civil_ship(Type t, string name, coordinates pos, double fuel, double lpm);
    virtual ~Civil_ship()=0;
    
    
    bool dock(weak_ptr<Port> port);
    void setDestination(weak_ptr<Port> port);
    bool refuel();
    void set_Waiting_for_fuel(bool b);
    bool isFuelling()const{return fuelling;};
    weak_ptr<Port> get_destination()const{return destination;};
    void enqueue(Civil_Ships_Commands *csc );
};

#endif /* Civil_ship_hpp */
