/*
 * EdgeCargo.h
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#ifndef EDGECARGO_H_
#define EDGECARGO_H_

#include "Edge.h"


class EdgeCargo: public Edge {
public:
	EdgeCargo(int,string);

	/* default CTORS */
	EdgeCargo()=default;
	EdgeCargo(const EdgeCargo&)=default;
	EdgeCargo& operator=(const EdgeCargo&)=default;
	EdgeCargo& operator=( EdgeCargo&&)=default;

	void updateEdge(const Edge&);

	virtual ~EdgeCargo();



};

#endif /* EDGECARGO_H_ */
