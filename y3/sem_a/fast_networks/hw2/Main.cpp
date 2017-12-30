/*
 * Main.cpp
 *
 *  Created on: 4 בדצמ× 2017
 *      Author: yaheltsu
 */
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

#define EMPTY -1

// generate inbound packets destination uniformly
void assign_destination(int* inbound, unsigned int N){

	for(unsigned int i=0; i<N; i++){
		if(inbound[i] == EMPTY){
			inbound[i] = rand() % N;
		}
	}
}

// mark outbound queues
void scatter_packets(int* inbound, bool* outbound, unsigned int N){

	for(unsigned int i=0; i<N; i++){
		int dest = inbound[i];
		if(outbound[dest] == false){
			outbound[dest] = true;
			inbound[i] = EMPTY;
		}
	}
}

double count_sent_packets(bool* outbound, unsigned int N){

	double sum=0;

	for(unsigned int i=0; i<N; i++){
		if(outbound[i]){
			sum++;
			outbound[i] = false;
		}
	}

	return sum;
}

double calc_throuput(unsigned int N, unsigned int ts){
	int* inbound = new int[N];
	bool* outbound = new bool[N];
	double sent_count = 0;

	srand(time(NULL));

	// init arrays
	for(unsigned int i=0; i<N; i++){
		inbound[i] = EMPTY;
		outbound[i] = false;
	}

	for(unsigned int i=0; i<ts; i++){

		assign_destination(inbound, N);

		scatter_packets(inbound, outbound, N);

		sent_count += count_sent_packets(outbound, N);
	}

	delete[] inbound;
	delete[] outbound;
	return sent_count / (N * ts);
}

int main(){
	unsigned int ts =10e6;
	unsigned int N = 50;
	double throuput;
	fstream csv{"out.csv", ios::out};
	csv<<"N , "<<"ts"<<endl;
	for(unsigned int n=2; n<=N; n++){
		throuput = calc_throuput(n,ts);
        cout<< n << "," << throuput << endl;
		csv<< n << "," << throuput << endl;
	}
	return 0;
}


