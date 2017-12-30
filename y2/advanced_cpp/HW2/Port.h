/*
 * Port.h
 *
 *  Created on: May 26, 2017
 *      Author: yali
 */

#ifndef PORT_H_
#define PORT_H_

#include <vector>
#include "Delivery.h"
#include <functional>

using std::vector;

// vertex class.
class Port {


public:

	Port()=default;
	Port(string&);
	Port(const Port&)=default;

	/* setters and getters */
	void setName(string&);
	const string& getName()const;

	// add inbound delivery to the port
	void addInDelivery(Delivery&);
	// add outbound delivery to the port
	void addOutDelivery(Delivery&);

	// amount o fcontainers in the port at a certain time
	int calculateAmountOfContainers(Date&);

	virtual ~Port();

private:
	const static int MAXNAMELEN=10;

	string name;
	vector<Delivery> outBound;		// record of all the outbound deliveries
	vector<Delivery> inBound;		// record of all the inbound deliveries

    // calculating function
    std::function<bool(const Delivery &,const Delivery &)> deliveryCmp=\
    [] (const Delivery &d1,const Delivery &d2) ->bool{
        return d1<d2;
    };
};

#endif /* PORT_H_ */
