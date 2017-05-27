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
	return getDestination() == e.getDestination();
}

void  Edge::setWeight(int w){
	weight = w;
}

int  Edge::getWeight()const{
	return weight;
}

void  Edge::setDestination(string d){
	dest=d;
}

string  Edge::getDestination()const{
    return dest;
}

Edge::~Edge() {}

