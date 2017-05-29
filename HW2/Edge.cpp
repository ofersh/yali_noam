/*
 * Edge.cpp
 *
 *  Created on: May 24, 2017
 *      Author: yali
 */

#include "Edge.h"
#include "Port.h"
using namespace std;

/* constructors */
Edge::Edge():weight(),dest() {}

Edge::Edge(int w,string d):weight(w),dest(d){}

// check if other edge has same destination
bool Edge::sameDestination(const Edge& e){
	return getDestination() == e.getDestination();
}

// operator ==
bool Edge::operator==(const Edge& rhs)const
{
    return dest==rhs.dest;
}

/* setters and getters */
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

// destructor
Edge::~Edge() {}

