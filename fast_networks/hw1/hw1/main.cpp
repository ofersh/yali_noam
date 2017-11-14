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

int main(int argc, const char * argv[]) {
	Dn_protocol dn;
	string input = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog.jpg";
	string destination = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog.bin";
	string final = "C:/Users/yali/Documents/GitHub/yali_noam/fast_networks/hw1/hw1/dog_out.jpg";
	dn.file_to_ip_packets(input, destination, 1, 2);
	dn.ip_packets_to_file(destination, final, 1, 2);

//	fstream check{ destination, ios_base::in | ios::binary };
//	char temp[20];
//	check.read(temp, 20);
//	for (int i = 0; i < 20; i++) {
//		unsigned int p = temp[i];
//		cout << p;
//	}
	
	return 0;
}
