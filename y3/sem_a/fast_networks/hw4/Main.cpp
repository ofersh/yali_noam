/*
 * Main.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#include "Router.h"
#include <iostream>

using namespace std;



int main(){

	int N=8, K=6, s;
	double p;

	s = 1;
	p = 0.5;

	Router router = Router(N, K);
	router.run(s, p);
	cout << "number of packets is:  " << router.pending_packets() << endl;

	return 0;
}
