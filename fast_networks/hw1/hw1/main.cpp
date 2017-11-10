//
//  main.cpp
//  hw1
//
//  Created by Noam Stolero on 10/11/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include <iostream>
#include <string>

#include "dn_protocol.h"

using namespace std;


int main(int argc, const char * argv[]) {
    string filename;
    Dn_protocol dn{};
    
    dn.prepare_file(filename);
    
    
    return 0;
}
