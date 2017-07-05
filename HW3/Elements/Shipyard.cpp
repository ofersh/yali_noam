/*
 * Shipyard.cpp
 *
 *  Created on: Jun 30, 2017
 *      Author: yali
 */

#include "Shipyard.h"


Shipyard& Shipyard::get_ship_factory(){
	static Shipyard shipyard;
	return shipyard;
}

Cruise_Ship* Shipyard::build_cruise_ship(string ship_name,double x,double y){
	Point p;
	p.x = x;
	p.y = y;
	return new Cruise_Ship(ship_name,p);
}
Cruiser* Shipyard::build_cruiser(string ship_name,double x,double y,int force,int range){
	Point p;
	p.x = x;
	p.y = y;
	return new Cruiser(ship_name,p,force,range);
}
Freighter* Shipyard::build_freighter(string ship_name,double x,double y,int container,int resistance){
	Point p;
	p.x = x;
	p.y = y;
	return new Freighter(ship_name,p,container,resistance);
}
