/*
 * Shipyard.h
 *
 *  Created on: Jun 30, 2017
 *      Author: yali
 */

#ifndef ELEMENTS_SHIPYARD_H_
#define ELEMENTS_SHIPYARD_H_

#include "Cruise_Ship.h"
#include "Cruiser.h"
#include "Freighter.h"


class Shipyard {
public:
	static Shipyard& get_ship_factory();
	~Shipyard()=default;

	shared_ptr<Cruise_Ship> build_cruise_ship(string ship_name,double x,double y);
	shared_ptr<Cruiser> build_cruiser(string ship_name,double x,double y,int force,int range);
	shared_ptr<Freighter> build_freighter(string ship_name,double x,double y,int container,int resistance);

	weak_ptr<Ship> findShip(string name);

private:

	vector<weak_ptr<Ship>> shipList;

	Shipyard()=default;

};

#endif /* SHIPYARD_H_ */
