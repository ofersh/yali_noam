
#include "Router.h"
#include <random>
#include <time.h>
#include <iostream>



Router::Router(int N, int K): input(N),  output(N), layers(K), N(N), K(K) {

	srand(time(nullptr));

	// Add the layers to demux
	for(int i=0; i<N; i++){
		input[i].add_layers(&layers, i);
		output[i].init_buffers(K);
		if(i < K){
			layers[i].setMux(&output);
		}
	}
}

Router::~Router() {
}

// Receive a packet from the web. If no packet as been received return -1
int generate_packet(double p, int N){

	double r = ((double) rand() / (RAND_MAX));
	if(r < p){
		return rand() % N;
	}

	return -1;
}

// Count all the packets in the router
double Router::pending_packets() {
	unsigned int all_packets = 0;

	for(Demux& d: input){
		all_packets += d.pending_packets();
	}

	for(Layer& l: layers){
		all_packets += l.pending_packets();
	}

	for(Mux& m: output){
		all_packets += m.pending_packets();
	}
	return all_packets;
}

// Check which layer to start sending to the output Mux
void Router::pull(int muxID){

	int best_fit = 0;
	int best_fit_ind = -1;
	vector<int> buffers = output[muxID].get_buffers();

	// Find the layer to start pulling from
	for (int i = 0; i < K; ++i) {
		if(buffers[i] == 0){
			int load = layers[i].get_load(muxID);
			if(load > best_fit){
				best_fit = load;
				best_fit_ind = i;
			}
		}
	}

	if(best_fit_ind != -1)
		layers[best_fit_ind].open_lane(muxID);

}



double Router::run(int s, double p) {
	double total_packets = 0;

	for (unsigned int iter = 0; iter < iterations; ++iter) {


		// Receive new packets from network and scatter
		for (int i = 0; i < N; i++)
			input[i].add_packet(generate_packet(p, N));

		// Emulate speed up s;
		for (int j = 0; j < s; ++j) {

			// Scatter to layers.
			for (int i = 0; i < N; i++)
				input[i].scatter();

			// Pull from layer
			for (int i = 0; i < N; i++)
				pull(i);

			// Scatter to mux.
			for (int i = 0; i < K ; i++)
				layers[i].scatter(i);
		}

		// Send packets to network
		for (int i = 0; i < N; i++)
			output[i].send_packet();

		total_packets += pending_packets();
	}

	return total_packets;
}

// Reset all the counters of the router
void Router::reset_router() {
	for(int i=0; i<N; i++){
		input[i].reset();
		output[i].reset();
		if(i < K){
			layers[i].reset();
		}
	}

}
