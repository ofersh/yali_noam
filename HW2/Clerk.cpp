//
//  Clerk.cpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "Clerk.hpp"

void Clerk::init_graphs(int len, char *files[]){
    string currentArg=files[1];
    
    if (currentArg!="-i")
        throw invalidInputException{"program arguments must start with -i"};
    
    for (int i=1 ; i<len || currentArg=="-o"; currentArg=files[++i]) {
        
        
        
    }
    
}
