/*
 * Demux.h
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#ifndef DEMUX_H_
#define DEMUX_H_

#include "Layer.h"


class Demux {
public:
	Demux();
	void add_layers(vector<Layer>* layers,  int i);
	void add_packet(int dest);
	void scatter();
	int pending_packets();
	void reset();
	virtual ~Demux() = default;

private:
	vector<Layer>* layers;
	vector<int> layers_q;
	vector<int> destination;
	int curr_index;
	int K;
};

#endif /* DEMUX_H_ */
