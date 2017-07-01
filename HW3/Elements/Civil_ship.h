//
//  Civil_ship.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Civil_ship_hpp
#define Civil_ship_hpp

#include "Ship.h"
#include "CivilShipsCommands.h"
#include <stdio.h>

class Civil_ship :public Ship {

private:
    constexpr static const double DOCKING_RANGE=0.1;

    weak_ptr<Port> destination;
    
public:
    Civil_ship(Type t, string name, int x, int y, double fuel);
    virtual ~Civil_ship()=0;
    
    
    void dock(weak_ptr<Port> port);
    void setDestination(weak_ptr<Port> port);
    void refuel();
    weak_ptr<Port> get_destination()const{return destination;};
    
    coordinates get_dest_coordinates()const;
    void enqueue(Civil_Ships_Commands *csc );
};

#endif /* Civil_ship_hpp */
