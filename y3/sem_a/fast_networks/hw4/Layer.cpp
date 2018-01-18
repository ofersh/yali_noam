/*
 * Layer.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Layer.h"
#include <iostream>



Layer::Layer(): destination(nullptr), N(0) {
}

void Layer::write_packet(int dest) {
	queues[dest]++;
}

int Layer::get_load(int muxID) {
	return queues[muxID];
}

void Layer::open_lane(int muxID) {
	writing[muxID] = true;
}

int Layer::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < N; ++i) {
		all_packets += queues[i];
	}
	return all_packets;

}


void Layer::scatter(int layerID) {

	for (int i=0 ; i<N ; i++){
		if(writing[i]){
			queues[i]--;
			(*destination)[i].write_packet(layerID);

			if( ! (*destination)[i].availble(layerID))
				writing[i] = false;
		}
	}
}

void Layer::setMux(vector<Mux>* dest)
{
	destination = dest;
	N = dest->size();
	reset();
}

void Layer::reset() {
	queues.assign(N,0);
	writing.assign(N,0);
}
