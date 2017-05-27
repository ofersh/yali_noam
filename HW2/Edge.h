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

using std::weak_ptr;
using std::shared_ptr;
using std::string;

class Edge {
public:

	Edge();
	Edge(int,weak_ptr<Port>);

	/* default CTORS */
	Edge(const Edge&)=default;
	Edge( Edge&&)=default;
	Edge& operator=(const Edge&)=default;
	Edge& operator=( Edge&&)=default;


	virtual void updateEdge(const Edge&)=0;
	virtual bool sameDestination(const Edge&);

	void setWeight(int w);
	int getWeight()const;
	void setDestination(weak_ptr<Port> d);
	string getDestination()const;

	virtual ~Edge();

private:
	int weight;
	weak_ptr<Port> dest;

};

#endif /* EDGE_H_ */
