/*
 * Delivery.h
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#ifndef DELIVERY_H_
#define DELIVERY_H_

#include "Date.h"

class Delivery {
	Date time;
	int cargo;
public:
	Delivery();
	Delivery(Date&,int);
	Delivery(const Delivery&);
	Delivery& operator=(const Delivery&);

	bool operator>(const Delivery&);
	bool operator<(const Delivery&);

	virtual ~Delivery();
};

#endif /* DELIVERY_H_ */
