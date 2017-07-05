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

	Cruise_Ship* build_cruise_ship(string ship_name,double x,double y);
	Cruiser* build_cruiser(string ship_name,double x,double y,int force,int range);
	Freighter* build_freighter(string ship_name,double x,double y,int container,int resistance);


private:
	Shipyard()=default;
	~Shipyard()=default;
};

#endif /* SHIPYARD_H_ */
