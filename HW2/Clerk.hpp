//
//  Clerk.hpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Clerk_hpp
#define Clerk_hpp

#include <stdio.h>
#include <unordered_map>
#include <memory>
#include "Port.h"
#include "Edge.h"
#include <stdexcept>

using std::unordered_map;
using std::runtime_error;

typedef vector<shared_ptr<Edge>> Edges;


class Clerk{
    
public:
    Clerk()=default;
    

    
    
    void init_graphs(int len, char *files[]);    //build graph using given files.
    
    void load(string fileName); //load a update file.
    
    
    
    
    
    
private:

    string outputFile;
    //map used as graphes.
    unordered_map<string,shared_ptr<Port>> portsMap;	//ports map.
    unordered_map<shared_ptr<Port>,Edges> edgesMap;
    
    
    
    /* HELPER METHODS */
    void readFIle(string fileName);
    
    
    
    
    
    /* coping is not permitted */
    Clerk(const Clerk &);
    Clerk(Clerk &&);
    Clerk& operator=(const Clerk &);
    Clerk& operator=(Clerk &&);
    /***************************/
    
    
    
    /* exceptions class */
    class openFileException: public runtime_error
    {
    public:
        openFileException(string what):runtime_error{what}{};
    };
    class invalidInputException: public runtime_error
    {
    public:
        invalidInputException(string what):runtime_error{what}{};
    };
    /*******************/

    
};


#endif /* Clerk_hpp */
