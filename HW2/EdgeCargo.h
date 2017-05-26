/*
 * EdgeCargo.h
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#ifndef EDGECARGO_H_
#define EDGECARGO_H_

#include "Edge.h"

#include <unordered_map>

using std::unordered_map;
using std:: string;
class EdgeCargo: public Edge {
public:
	EdgeCargo();
	virtual ~EdgeCargo();


private:
	unordered_map<string,shared_ptr<Port>>;

};

#endif /* EDGECARGO_H_ */
