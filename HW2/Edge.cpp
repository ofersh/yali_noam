/*
 * Edge.cpp
 *
 *  Created on: May 24, 2017
 *      Author: yali
 */

#include "Edge.h"
#include "Port.h"
using namespace std;


Edge::Edge():weight(),dest() {}

Edge::Edge(int w,string d):weight(w),dest(d){}

bool Edge::sameDestination(const Edge& e){
	if(this->dest.expired() || e.dest.expired())
		return false;
	return getDestination() == e.getDestination();
}

void  Edge::setWeight(int w){
	weight = w;
}

int  Edge::getWeight()const{
	return weight;
}

void  Edge::setDestination(weak_ptr<Port> d){
	dest=d;
}

string  Edge::getDestination()const{
	return dest.lock()->getName();
}

Edge::~Edge() {}

