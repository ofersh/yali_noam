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

void Clerk::init_graphs(int len, char *files[]){
    string currentArg=files[1];
    int i=0;
    
    if (currentArg!="-i")
        throw invalidInputException{"program arguments must start with -i"};
    
    /*
     read all input files
     */
    for (i=1 ; i<len || currentArg!="-o"; currentArg=files[++i])
    {
        try {
            readFIle(currentArg);
        }catch(invalidInputException &e)
        {
            cerr<<e.what()<<endl;
            exit(1);
        }
    }
    /* set output file.*/
    if (i!=len && currentArg=="-o")
        outputFile=currentArg;
    else
        outputFile="output.dat";
}


void Clerk::readFIle(string fileName){
    ifstream inputFile{fileName};
    string line, outBoundport, outBoundDate;

    //handle first line
    getline(inputFile,line , ",");
    
}








