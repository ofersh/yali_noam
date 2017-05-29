/*
 * EdgeCargo.cpp
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#include "EdgeCargo.h"


EdgeCargo::EdgeCargo(int w,string d):Edge(w,d){}

// calculate the new weight
void EdgeCargo::updateEdge(const Edge& e){
	// calculates the amount of all the containers passed over the egde
	int weight = getWeight() + e.getWeight();
	setWeight(weight);
}

EdgeCargo::~EdgeCargo() {}

