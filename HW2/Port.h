/*
 * Port.h
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#ifndef PORT_H_
#define PORT_H_

#include "Edge.h"
#include "C:\Users\yali\git\yali_noam\cpp\HW_2\Delivery.h"
#include <vector>


class Port {
public:
	Port();
	Port(std::string,std::shared_ptr<std::vector<Delivery>>&);

	void addEdge(Edge&);
	void removeEdge(Port&);
	void addDelivery(Delivery&);
	void removeDelivery(Date&);

	void setDeliveryTable(std::shared_ptr<std::vector<Delivery>>&);
	void setName(std::string&);
	std::shared_ptr<std::vector<Delivery>>& getDeliveryTable();
	std::string& getName()const;

	int calculateAmountOfContainers(Date&);
	std::vector<Edge>& getAllOutboundPorts()const;
	void print();

	virtual ~Port();

private:
	std::string name;
	std::vector<Edge> edges;			/* need to find a way to make it hold derived objects */
	std::shared_ptr<std::vector<Delivery>> deliverys;

	Edge& getEdge(std::string);
};

#endif /* PORT_H_ */
