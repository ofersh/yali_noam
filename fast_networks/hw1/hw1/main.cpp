//
//  main.cpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

#include "dn_protocol.h"

using namespace std;

void test_endian(){

	short tmp_s = 1;
	char* tmp_c = reinterpret_cast<char*>(&tmp_s);
	if(tmp_c[0] == 1)
		cout << "I'm little endian" << endl;
	else
		cout << "I'm big endian" << endl;

	int tmp_i = 1;
	tmp_c = reinterpret_cast<char*>(&tmp_i);

	cout << "0 - " << (int)tmp_c[0] << "|1 - " << (int)tmp_c[1] << "|2 - " << (int)tmp_c[2] << "|3 - " << (int)tmp_c[3] << endl;

	short* ps = reinterpret_cast<short*>(&tmp_i);

	cout << "0 - " << ps[0] << "| 1 - " << ps[1] << endl;

	exit(0);

}




int main(int argc, const char * argv[]) {

	Dn_protocol dn;
	string input = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/shtil.jpg";
	string network = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/shtil.bin";
	string destination = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/shtil_out.jpg";
	cout << "Writing " << input << " to the network" << endl;
	if(!dn.file_to_ip_packets(input, network, 1, 2)){
		cout << "Failed to write the packets" << endl;
		exit(1);
	}
	cout << "Finished writing " << input << " to the network" << endl;

	cout << "Reading to " << destination << " from the network" << endl;
	if(!dn.ip_packets_to_file(network, destination, 1, 2)){
		cout << "Failed to read the packets" << endl;
		exit(1);
	}

	cout << "Finished reading to " << destination << " from the network" << endl;

	//	Dn_protocol dn;
	//	string input = "C:/Users/stell/git/yali_noam/fast_networks/hw1/hw1/shtil.jpg";
	//	string destination = "C:/Users/stell/git/yali_noam/fast_networks/hw1/hw1/out.bin";
	//	dn.file_to_ip_packets(input, destination, 1, 2);
	//

	return 0;
}
