/*
 * Mux.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Mux.h"
#include <iostream>


Mux::Mux(): K(0), last_sent_ind(0) {}


void Mux::write_packet(int from) {
	buffers[from]++;
}

void Mux::init_buffers(int k) {
	K=k;
	buffers.assign(K,0);
}

void Mux::send_packet() {
	for (int i = 0; i < K; ++i) {
		int current = (i+last_sent_ind) % K;
		if (buffers[current] == K){
			buffers[current] -= K ;
			last_sent_ind++;
			break;
		}
	}
}

// check if buffer has space
bool Mux::availble(int i) {
	return buffers[i]!=K;
}

vector<int> Mux::get_buffers() {
	return buffers;
}

int Mux::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < K; ++i) {
		all_packets += buffers[i];
	}
	return all_packets;

}
