/*
 * Port.cpp
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#include "Port.h"


using namespace std;


Port::Port():name(),edges(),deliverys(NULL){}

Port::Port(std::string n,std::shared_ptr<std::vector<Delivery>>& d):name(n),edges(),deliverys(d){}


Edge& getEdge(std::string){
	/* TODO:check if the edge exists
	 * if so, return it else return  null
	 */
}


void Port::addEdge(Edge& e){
	/* TODO:check if edge exists.
	 * if not, add. if exists operator+
	 */
}
void Port::removeEdge(Port& p){
	/* TODO:check if edge exists.
	 * if not, do nothing. if exists remove
	 */
}
void Port::addDelivery(Delivery& d){

}


void Port::setDeliveryTable(std::shared_ptr<std::vector<Delivery>>& deliveryTable){
	deliverys = deliveryTable;
}
//void Port::setName(std::string&);
//std::shared_ptr<std::vector<Delivery>>& Port::getDeliveryTable();
//std::string& Port::getName()const;
//
//int Port::calculateAmountOfContainers(Date&);
//std::vector<Edge>& Port::getAllOutboundPorts()const;
//void Port::print();

Port::~Port() {
}

