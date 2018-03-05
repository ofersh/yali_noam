
#include "Mux.h"
#include <iostream>


Mux::Mux(): K(0), last_sent_ind(0) {}

// Write a packet to the given queue of the Mux
void Mux::write_packet(int from) {
	buffers[from]++;
}

// Initialize the buffers
void Mux::init_buffers(int k) {
	K=k;
	reset();
}

// If a queue is full, send the packet to the web
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

// Check if buffer has space
bool Mux::availble(int i) {
	return buffers[i]!=K;
}

vector<int> Mux::get_buffers() {
	return buffers;
}

// Count all the packets that are currently in the Mux
int Mux::pending_packets() {
	int all_packets = 0;
	for (int i = 0; i < K; ++i) {
		all_packets += buffers[i];
	}
	return all_packets;
}

// Reset all the counters of the Mux
void Mux::reset() {
	buffers.assign(K,0);
}
