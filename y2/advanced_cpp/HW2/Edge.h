/*
 * Edge.h
 *
 *  Created on: May 24, 2017
 *      Author: yali
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <memory>
#include <string>

class Port;

using std::string;

class Edge {
public:

	/* constructors */
	Edge();
	Edge(int,string);

	/* default CTORS */
	Edge(const Edge&)=default;
	Edge( Edge&&)=default;
	Edge& operator=(const Edge&)=default;
	Edge& operator=( Edge&&)=default;


    bool operator==(const Edge & )const;
    
    // abstract function. derived object implementation needed
	virtual void updateEdge(const Edge&)=0;

	// check if edge has same destination
	virtual bool sameDestination(const Edge&);

	/* setters and getters */
	void setWeight(int w);
	int getWeight()const;
	void setDestination(string d);
	string getDestination()const;

	virtual ~Edge();

private:
	int weight;
	string dest;
};

#endif /* EDGE_H_ */
