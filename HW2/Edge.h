/*
 * Edge.h
 *
 *  Created on: May 24, 2017
 *      Author: yali
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <memory>
class Port;


class Edge {
private:
	int weight;
	std::weak_ptr<Port> dest;

public:

	Edge();
	Edge(int,std::weak_ptr<Port>);
	/* default copy constructors might be sufficient

	Edge(const Edge&);
	Edge(const Edge&&);
	Edge& operator=(const Edge&);
	Edge& operator=(const Edge&&);
*/

	virtual void updateEdge(const Edge&)=0;
	virtual bool operator==(const Edge&);

	virtual ~Edge();
};

#endif /* EDGE_H_ */
