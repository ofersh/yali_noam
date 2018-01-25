/*
 * Mux.h
 *
 *  Created on: 16 Jan 2018
 *      Author: noam
 */

#ifndef MUX_H_
#define MUX_H_

#include <vector>
using namespace std;

class Mux {
public:
	Mux();
	void init_buffers(int k);
	void write_packet(int from);
	void send_packet();
	bool availble(int i);
	vector<int> get_buffers();
	int pending_packets();
	void reset();
	virtual ~Mux()=default;

private:
	vector<int> buffers;
	int K;
	int last_sent_ind;

};

#endif /* MUX_H_ */
