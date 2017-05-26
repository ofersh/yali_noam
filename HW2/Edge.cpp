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

Edge::Edge(int w,weak_ptr<Port> d):weight(w),dest(d){}

bool Edge::operator==(const Edge& e){
	/*
	shared_ptr<Port> a,b;
	a = dest.lock();
	b = e.dest.lock();
	return a->getName()==b->getName();
	*/
	//return dest.lock()->getName()==e.dest.lock()->getName();
	return true;
}

Edge::~Edge() {}

