/*
 * EdgeTime.h
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#ifndef EDGETIME_H_
#define EDGETIME_H_

#include "Edge.h"

class EdgeTime: public Edge {
public:
	EdgeTime();
	virtual ~EdgeTime();


private:
	int travels_counter;
};

#endif /* EDGETIME_H_ */
