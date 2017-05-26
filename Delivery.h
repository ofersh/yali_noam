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
	int cargo;

	void setDeliveryDetails(Date&,int);
public:
	Delivery();
	Delivery(Date&,int);
	/* default sufficient
	Delivery(const Delivery&);
	Delivery(const Delivery&&);
	Delivery& operator=(const Delivery&);
	Delivery& operator=(const Delivery&&);
*/

	void setNewDelivery(Date&,int);

	bool operator>(const Delivery&);
	bool operator<(const Delivery&);

	virtual ~Delivery();

	int getCargo() const;
};

#endif /* DELIVERY_H_ */
