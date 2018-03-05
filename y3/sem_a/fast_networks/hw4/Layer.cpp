

#include "Layer.h"
#include <iostream>



Layer::Layer(): destination(nullptr), N(0) {
}

// Write the packet in the layer
void Layer::write_packet(int dest) {
	queues[dest]++;
}

// Return how much packets are currently in the given output queue
int Layer::get_load(int muxID) {
	return queues[muxID];
}

// Set to start sending message to the output
void Layer::open_lane(int muxID) {
	writing[muxID] = true;
}

// Count all the packets in the layer
int Layer::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < N; ++i) {
		all_packets += queues[i];
	}
	return all_packets;
}

// Write the packets in the output queue
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

// Add Muxes to the layer
void Layer::setMux(vector<Mux>* dest)
{
	destination = dest;
	N = dest->size();
	reset();
}

// Reset all the counters of the layer
void Layer::reset() {
	queues.assign(N,0);
	writing.assign(N,0);
}
