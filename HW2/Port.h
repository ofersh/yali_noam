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

using std::shared_ptr;
using std::vector;

// vertex class.
class Port {


public:

	Port()=default;
	Port(string&);
	Port(const Port&)=default;


	void setName(string&);
	const string& getName()const;

	void addInDelivery(Delivery&);
	void addOutDelivery(Delivery&);


	int calculateAmountOfContainers(Date&);

	virtual ~Port();

private:
	const static int MAXNAMELEN=10;

	string name;
	vector<Delivery> outBound;
	vector<Delivery> inBound;

};

#endif /* PORT_H_ */
