/*
 * Port.h
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#ifndef PORT_H_
#define PORT_H_

#include "Edge.h"
#include <vector>
#include "Delivery.h"

using std::shared_ptr;
using std::vector;

// vertex class.
class Port {


public:

	Port();
	Port(string,shared_ptr<vector<Delivery>>&);

	void addEdge(Edge&);
	void removeEdge(Port&);
	void addDelivery(Delivery&);
	void removeDelivery(Date&);

	void setDeliveryTable(shared_ptr<vector<Delivery>>&);
	void setName(string&);
	shared_ptr<vector<Delivery>>& getDeliveryTable();
	string& getName()const;

	int calculateAmountOfContainers(Date&);
	vector<Edge>& getAllOutboundPorts()const;
	void print();

	virtual ~Port();

private:
	string name;
	vector<shared_ptr<Edge>> edges;			/* need to find a way to make it hold derived objects */
	shared_ptr<vector<Delivery>> deliverys;

	Edge& getEdge(string);
};

#endif /* PORT_H_ */
