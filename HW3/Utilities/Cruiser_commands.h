//
//  Cruiser_commands.hpp
//  hw3
//
//  Created by Noam Stolero on 01/07/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Cruiser_commands_h
#define Cruiser_commands_h

#include <stdio.h>
#include "Ships_commands.h"
#include "../Elements/Cruiser.h"


class Cruiser_commands :public Ships_commands {
public:

	Cruiser_commands();
	~Cruiser_commands();
	virtual void operator()(Cruiser *)=0;

};

class Attack : public Cruiser_commands{
	Attack(weak_ptr<Ship> attackedShip): attackedShip(attackedShip){};
	~Attack();

	void operator()(Cruiser* c){
		c->attack(attackedShip);
	}

private:
	weak_ptr<Ship> attackedShip;
}


#endif /* Cruiser_commands_hpp */
