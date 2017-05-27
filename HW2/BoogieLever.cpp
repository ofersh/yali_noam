//
//  BoogieLever.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "BoogieLever.hpp"


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
