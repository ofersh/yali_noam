/*
 * Router.h
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include "Mux.h"
#include "Demux.h"


class Router {
public:
	const unsigned int iterations=10e5;

	Router(int N, int K);
	double run(int s, double p);
	double pending_packets();
	void reset_router();
	virtual ~Router();

private:
	void pull(int muxID);

	vector<Demux> input;
	vector<Mux> output;
	vector<Layer> layers;
	int N;
	int K;

};

#endif /* ROUTER_H_ */
