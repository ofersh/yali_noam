/*
 * Mux.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Mux.h"
#include <iostream>


Mux::Mux(): buffers(nullptr), K(0), last_sent_ind(0) {}

Mux::~Mux() {
	delete[] buffers;
}

void Mux::write_packet(int from) {
	buffers[from]++;
}

void Mux::init_buffers(int k) {
	K=k;
	buffers = new int[K]();
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

int* Mux::get_buffers() {
	return buffers;
}

int Mux::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < K; ++i) {
		all_packets += buffers[i];
	}
	return all_packets;

}
