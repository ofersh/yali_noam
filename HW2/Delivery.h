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
private:
	Date time;
	unsigned int cargo;

	void setDeliveryDetails(Date&,int);
public:
	Delivery();
	Delivery(Date&,int);
	/* default CTOR */
	Delivery(const Delivery&)=default;
	Delivery(Delivery&&)=default;
	Delivery& operator=(const Delivery&)=default;
	Delivery& operator=(Delivery&&)=default;


	void setNewDelivery(Date&,int);

	void addCargo(int);

	bool operator>(const Delivery&);
	bool operator<(const Delivery&);

	virtual ~Delivery();

	int getCargo() const;
};

#endif /* DELIVERY_H_ */
