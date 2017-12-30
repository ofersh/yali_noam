

#ifndef Utilities_Cruiser_commands_h
#define Utilities_Cruiser_commands_h

#include <stdio.h>
#include "Ships_commands.h"
#include "../Elements/Cruiser.h"
#include "../Elements/Civil_ship.h"

class Cruiser_commands :public Ships_commands {
public:

	Cruiser_commands()=default;
	~Cruiser_commands()=default;
	virtual bool operator()(Cruiser *)=0;
	virtual bool operator()(Ship * s){ return operator ()(dynamic_cast<Cruiser*>(s));}

};

class Attack : public Cruiser_commands{
public:
	Attack(weak_ptr<Ship> attackedShip): attackedShip(attackedShip){};
	~Attack()=default;

	bool operator()(Cruiser* c){

		return true;
	}

private:
	weak_ptr<Ship> attackedShip;
};


#endif /* Cruiser_commands_hpp */
