/*
 * GraphPorts.h
 *
 *  Created on: 26 May 2017
 *      Author: noam
 */

#ifndef GRAPHPORTS_H_
#define GRAPHPORTS_H_


#include <unordered_map>
#include "Edge.h"
#include "Port.h"


using std::unordered_map;
typedef vector<shared_ptr<Edge>> Edges;


class GraphPorts {
public:
	GraphPorts();
	virtual ~GraphPorts();

	void addPort(Port& port);
	Edges getEdges(string portName);
	void addEdge(Edge& edge);
	void removeEdge(string srcPort,string destPort );

private:

	unordered_map<string,shared_ptr<Port>> portsMap;	//ports map.
	unordered_map<shared_ptr<Port>,Edges> edgesMap;


};

#endif /* GRAPHPORTS_H_ */
