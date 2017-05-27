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
#include <sstream>

using std::unordered_map;
using std::runtime_error;
using std::ostringstream;
using std::ifstream;
class InvalidInputException;

typedef vector<shared_ptr<Edge>> Edges;


class Clerk{
    
public:
    Clerk()=default;
    
    
    void load(string fileName); //load a update file.
    void setOutputFile(string fileName){outputFile=fileName;};
    
private:

    string outputFile;
    //map used as graphes.
    unordered_map<string,shared_ptr<Port>> portsMap;	//ports map.
    unordered_map<string,Edges> timeEdgesMap;
    unordered_map<string,Edges> cargoEdgesMap;
    
    
    
    /* HELPER METHODS */
    void readFIle(string fileName);
    Date handleFirstLine(ifstream &, string fileName, string &outBoundPortName);
    
    
    
    
    
    
    /* coping is not permitted */
    Clerk(const Clerk &);
    Clerk(Clerk &&);
    Clerk& operator=(const Clerk &);
    Clerk& operator=(Clerk &&);
    /***************************/
    
    
    
    /* exceptions class */
    class OpenFileException: public runtime_error
    {
    public:
        OpenFileException(string what):runtime_error{what}{};
        static OpenFileException getExcept(string name, int lineNum){
            ostringstream os;
            os<<"Invalid input in file "<<name<<" at line "<<0<<".\n";
            return OpenFileException{os.str()};
        };
    };
    class InvalidInputException: public runtime_error
    {
    public:
        InvalidInputException(string what):runtime_error{what}{};
        static InvalidInputException getExcept(string name, int lineNum){
            ostringstream os;
            os<<"Invalid input in file "<<name<<" at line "<<lineNum<<".\n";
            return InvalidInputException{os.str()};
        };
    };
    /*******************/

    
};


#endif /* Clerk_hpp */
