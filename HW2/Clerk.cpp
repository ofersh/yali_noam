//
//  Clerk.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "Clerk.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::endl;
using std::ifstream;
using std::string;




void Clerk::readFIle(string fileName){
    ifstream inputFile{fileName};
    string line, outBoundport, outBoundDate;

    //handle first line
    getline(inputFile,line , ",");
    
}








