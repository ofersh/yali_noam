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

    
public:
    void dock(weak_ptr<Port> portName);
    void setDestination(weak_ptr<Port> portName);
    void enqueue(Civil_Ships_Commands *csc );
};

#endif /* Civil_ship_hpp */
