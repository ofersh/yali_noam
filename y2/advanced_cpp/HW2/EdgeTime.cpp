/*
 * EdgeTime.cpp
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#include "EdgeTime.h"


EdgeTime::EdgeTime():Edge(),travels_counter(1){}

EdgeTime::EdgeTime(int w, string d):Edge(w,d),travels_counter(1){}

// calculate the new weight of the edge
void EdgeTime::updateEdge(const Edge& e){
	// calculates the avg time to pass on the edge
	int oldWeight = getWeight() * travels_counter;
	travels_counter++;
	int newWeight = (oldWeight + e.getWeight())/travels_counter;
	setWeight(newWeight);
}

EdgeTime::~EdgeTime(){}


