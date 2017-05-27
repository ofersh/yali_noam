/*
 * EdgeCargo.cpp
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#include "EdgeCargo.h"

EdgeCargo::EdgeCargo(int w,weak_ptr<Port> d):Edge(w,d){}


void EdgeCargo::updateEdge(const Edge& e){
	int weight = getWeight() + e.getWeight();
	setWeight(weight);
}

EdgeCargo::~EdgeCargo() {}

