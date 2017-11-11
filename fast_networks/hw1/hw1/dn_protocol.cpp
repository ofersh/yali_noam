//
//  dn_protocol.cpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "dn_protocol.h"
#include <fstream>
using namespace std;

const int PACKET_LENGTH = 256;

void Dn_protocol::prepare_file(string filename){
    fstream fin{filename, ios_base::in | ios_base::binary};
    char packet[PACKET_LENGTH];
    
    while (int true_length = fin.read(packet, PACKET_LENGTH)) {
        <#statements#>
    }
    
    
}
