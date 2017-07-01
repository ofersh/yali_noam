/*
 * Shipyard.h
 *
 *  Created on: Jun 30, 2017
 *      Author: yali
 */

#ifndef SHIPYARD_H_
#define SHIPYARD_H_

#include "Cruise_Ship.h"
#include "Cruiser.h"
#include "Freighter.h"


class Shipyard {
public:
	Shipyard()=delete;
	virtual ~Shipyard()=delete;

	static Cruise_Ship* build_cruise_ship();
	static Cruiser* build_cruiser();
	static Freighter* build_freighter();

};

#endif /* SHIPYARD_H_ */
