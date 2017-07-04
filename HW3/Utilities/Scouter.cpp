/*
 * Scouter.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "Scouter.h"

Scouter::Scouter() {}

Scouter::~Scouter() {}

Point Scouter::getDestCoordinates()const {
	return destination;
}

double Scouter::calculate_distance(const Point & from, const Point & to){
	Cartesian_vector cv;
	Polar_vector pv;

	cv.delta_x = to.x-from.x;
	cv.delta_y = to.y-from.y;

	pv = cv;

	return pv.r;
}



Point Scouter::calculateNextStep(const Point current){
	Point newPoint;
	Cartesian_vector cv;
	Polar_vector pv;

	// check if the distance is less then one move of the ship
	if(calculate_distance(current,destination) < velocity)
		return destination;

	pv.r = velocity;
	pv.theta = azimuth;

	cv = pv;
	newPoint.x = current.x + cv.delta_x;
	newPoint.y = current.y + cv.delta_y;

	return newPoint;
}
