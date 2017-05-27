/*
 * Port.cpp
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#include "Port.h"
#include <algorithm>

using namespace std;

Port::Port(string& n):name{n}
{
}

void Port::setName(string& n){
	name = n;
}
string& Port::getName()const{
	return name;
}

void Port::addInDelivery(Delivery& inD){
	inBound.push_back(inD);
}
void Port::addOutDelivery(Delivery& outD){
	outBound.push_back(outD);
}


int Port::calculateAmountOfContainers(Date& d){
	sort(inBound.begin(),inBound.end());
	sort(outBound.begin(),outBound.end());
	int currentNumberOfContainers=0;
	for (std::vector<Delivery>::iterator it = inBound.begin() ; it != inBound.end() && d<(*it); ++it)
	    currentNumberOfContainers += it->getCargo();
	for (std::vector<Delivery>::iterator it = outBound.begin() ; it != outBound.end() && d<(*it); ++it)
		    currentNumberOfContainers -= it->getCargo();
	return currentNumberOfContainers;
}

Port::~Port() {
}

