/*
 * Delivery.cpp
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#include "Delivery.h"

/* constructors */
Delivery::Delivery():time(),cargo() {}

Delivery::Delivery(Date& t,int c){
	setDeliveryDetails(t,c);
}

// set delivery details
void Delivery::setDeliveryDetails(Date& t,int c){
	time = t;
	cargo = c;
}

// add delivery details
void Delivery::setNewDelivery(Date& t,int c){
	setDeliveryDetails(t,c);
}


/* getters */
const Date& Delivery::getDate()const{
	return time;
}

int Delivery::getCargo() const{
	return cargo;
}

// add another cargo to the delivery
void Delivery::addCargo(int cargo){
	this->cargo += cargo;
}


/* Delivery operators */

bool Delivery::operator>(const Delivery& rhs)const{
	return time>rhs.time;
}

bool Delivery::operator==(const Delivery &rhs)const{
    return time==rhs.time;
}

bool Delivery::operator<(const Delivery& rhs)const{
	return time<rhs.time;
}


Delivery::~Delivery() {}

