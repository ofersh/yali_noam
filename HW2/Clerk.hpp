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
using std::shared_ptr;
using std::ostream;

class InvalidInputException;

typedef vector<shared_ptr<Edge>> Edges;


class Clerk{
    
public:
    Clerk()=default;
    
    
    void load(string fileName); //load a update file.
    void setOutputFile(string fileName){outputFile=fileName;}; //set output file.
    
    /* quary functions */

    // get all the outbound edges from a given port
    void outboundQuery(string port);

    // get all the inbound edges to a given port
	void inboundQuery(string port);

	// caluclate the amount of containers in a gicen port at a given date
	void balance(string port,string date);

	// print the graph to the file
	void print();



private:

    string outputFile;
    //map used as graphes.
    unordered_map<string,Port> portsMap;	//ports map.
    unordered_map<string,Edges> timeEdgesMap;
    unordered_map<string,Edges> cargoEdgesMap;
    
    
    
    /* HELPER METHODS */
    void readFIle(string fileName);
    // check the file for wrong input
    void verifyInputFile(string fileName);

    //first line handler.
    Date handleFirstLine(string &, string fileName, string &outBoundPortName);
    void addEdges(string rootPort, string lastPort); //create and add new edges.
    void updateRecvPort();  //update recv port.
    void updateRootPort(string rootPortName, Date rootOutBound); //update root port.
    //added a single edge to any of the graph.
    void addNewEdge(string portName, shared_ptr<Edge> newEdge,unordered_map<string,Edges> &graph);
    
    
    /* print functions */
    // print the edges of a port
    void printPort(ostream& out,Edges& E);
    // print a graph to the ostream
    void printGraph(ostream& out,string type,unordered_map<string,Edges>& map);
    
    /* coping is not permitted */
    Clerk(const Clerk &);
    Clerk(Clerk &&);
    Clerk& operator=(const Clerk &);
    Clerk& operator=(Clerk &&);
    /***************************/
    
    
    //struct to hold a current line.
    struct Transaction_Info{
        string inBoundDateStr,outBoundDateStr, inBoundPortName,cargoStr;
        Date inBoundDate, outBoundDate;
        int cargoAmount;
        void setInfo(string line,string fileName, int lineNum);
    }trans_info;
    
    
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
