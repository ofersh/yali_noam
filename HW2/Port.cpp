/*
 * Port.cpp
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#include "Port.h"
#include <algorithm>

using namespace std;

// constructor
Port::Port(string& n):name{n}
{
}

/* getters and setters */
void Port::setName(string& n){
	name = n;
}
const string& Port::getName()const{
	return name;
}

// add inbound delivery to the records
void Port::addInDelivery(Delivery& inD){
	inBound.push_back(inD);
}

// add outbound delivery to the records
void Port::addOutDelivery(Delivery& outD){
	outBound.push_back(outD);
}

// calculating amoun of containers in a given time
int Port::calculateAmountOfContainers(Date& d){

	// sorting the records
	sort(inBound.begin(),inBound.end(),deliveryCmp);
	sort(outBound.begin(),outBound.end(),deliveryCmp);

	int currentNumberOfContainers=0;
	// calculate the inbound deliveries. add the number of containers to the sum
	for (std::vector<Delivery>::iterator it = inBound.begin() ; it != inBound.end() ; ++it){
		if(d<it->getDate())
			break;
		currentNumberOfContainers += it->getCargo();
	}
	// calculate the outbound deliveries. sub the number of containers from the sum
	for (std::vector<Delivery>::iterator it = outBound.begin() ; it != outBound.end(); ++it){
		if(d<it->getDate())
			break;
		currentNumberOfContainers -= it->getCargo();
	}


	return currentNumberOfContainers;
}

Port::~Port() {}


