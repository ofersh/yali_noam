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
	// necessary constructors
	Delivery();
	Delivery(Date&,int);
	/* default CTOR */
	Delivery(const Delivery&)=default;
	Delivery(Delivery&&)=default;
	Delivery& operator=(const Delivery&)=default;
	Delivery& operator=(Delivery&&)=default;

	// add delivery details
	void setNewDelivery(Date&,int);

	// get the date of the buffer
	const Date& getDate()const;
	int getCargo() const;

	// add cargo to the delivery
	void addCargo(int);

	// Delivery operators
	bool operator>(const Delivery&)const;
    bool operator==(const Delivery&)const;
	bool operator<(const Delivery&)const;

	// Delivery destructor
	virtual ~Delivery();
};

#endif /* DELIVERY_H_ */
