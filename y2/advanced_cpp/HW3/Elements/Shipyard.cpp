
#include "Shipyard.h"

// meyers singelton.
Shipyard& Shipyard::get_ship_factory(){
	static Shipyard shipyard;
	return shipyard;
}

//cruise_ship creater.
shared_ptr<Cruise_Ship> Shipyard::build_cruise_ship(string ship_name,double x,double y){
	Point p;
	p.x = x;
	p.y = y;
	shared_ptr<Cruise_Ship> newShip(new Cruise_Ship(ship_name,p));
	shipList.push_back(newShip);
	return newShip;
}

//Cruiser creator.
shared_ptr<Cruiser> Shipyard::build_cruiser(string ship_name,double x,double y,int force,int range){
	Point p;
	p.x = x;
	p.y = y;
	shared_ptr<Cruiser> newShip(new Cruiser(ship_name,p,force,range));
	shipList.push_back(newShip);
	return newShip;
}

//Freighter Creator.
shared_ptr<Freighter> Shipyard::build_freighter(string ship_name,double x,double y,int container,int resistance){
	Point p;
	p.x = x;
	p.y = y;
	shared_ptr<Freighter> newShip(new Freighter(ship_name,p,container,resistance));
	shipList.push_back(newShip);
	return newShip;
}


//find a ship by name.
weak_ptr<Ship> Shipyard::findShip(string name){
	for(weak_ptr<Ship> theShip : shipList){
		if(theShip.expired())
			continue;
		if(theShip.lock()->getName() == name)
			return theShip;
	}

	return weak_ptr<Ship>();
}
