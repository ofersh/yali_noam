/*
 * Delivery.cpp
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#include "Delivery.h"

Delivery::Delivery():time(),cargo() {}

Delivery::Delivery(Date& t,int c){
	setDeliveryDetails(t,c);
}

void Delivery::setDeliveryDetails(Date& t,int c){
	time = t;
	cargo = c;
}

void Delivery::setNewDelivery(Date& t,int c){
	setDeliveryDetails(t,c);
}

const Date& Delivery::getDate()const{
	return time;
}

void Delivery::addCargo(int cargo){
	this->cargo += cargo;
}

bool Delivery::operator>(const Delivery& rhs){
	return time>rhs.time;
}

bool Delivery::operator==(const Delivery &rhs){
    return time==rhs.time;
}

bool Delivery::operator<(const Delivery& rhs){
	return time<rhs.time;
}

int Delivery::getCargo() const{
	return cargo;
}

Delivery::~Delivery() {}

