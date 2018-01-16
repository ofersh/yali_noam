/*
 * Demux.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Demux.h"
#include <iostream>

Demux::Demux(): layers(nullptr), layers_q(nullptr), destination(nullptr), curr_index(0), K(0) {}

void Demux::add_layers(vector<Layer>* layers, int i) {
	this->layers = layers;
	K = layers->size();
	layers_q = new int[K]();
	destination = new int[K]();
	curr_index = i;
}

void Demux::add_packet(int dest) {
	if(dest < 0)
		return;

	layers_q[curr_index] = K;
	destination[curr_index] = dest;
	curr_index = (curr_index+1) % K;

}

void Demux::scatter() {
	for(int i=0; i<K; i++){
		if(layers_q[i] != 0){
			(*layers)[i].write_packet(destination[i]);
			layers_q[i]--;
		}
	}
}

int Demux::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < K; ++i) {
		all_packets += layers_q[i];
	}
	return all_packets;
}

Demux::~Demux() {
	delete[] destination;
	delete[] layers_q;
}

