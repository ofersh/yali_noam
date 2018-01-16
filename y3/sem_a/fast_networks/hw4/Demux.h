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
	virtual ~Demux();

private:
	vector<Layer>* layers;
	int* layers_q;
	int* destination;
	int curr_index;
	int K;
};

#endif /* DEMUX_H_ */
