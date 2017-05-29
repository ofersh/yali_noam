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
#include <sstream>
#include <string>
#include "EdgeTime.h"
#include "EdgeCargo.h"
#include <algorithm>

using std::cout;
using std::ofstream;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::stoi;
using std::for_each;
using std::shared_ptr;
using std::find;
using std::stringstream;

static const string ALPHA{"abcdefghijklmnopqrstuvwxyz\
    ABCDEFGHIJKLMNOPQRSTUVWXYZ "},\
DATE{"0123456789:/ "},\
NUMBERS{"0123456789"};



//load a given file with transaction.
void Clerk::load(string fileName)
{
    //first verify input file.
    verifyInputFile(fileName);
    
    //open file for reading.
    ifstream inputFile{fileName};
    if (inputFile.fail())
        throw OpenFileException::getExcept(fileName, 0);
    
    //save root port, and last handled port.
    string rootPortName,line, lastPortName;
    
    getline(inputFile, line);
    
    //first line need special treatment.
    Date RootOutBoundDate=handleFirstLine(line, fileName, rootPortName);
    trans_info.outBoundDate=RootOutBoundDate;
   
    //read line by line each port in the journey.
    lastPortName=rootPortName;
    int lineNum=2;
    getline(inputFile, line);
    do{
        //read transaction data.
        trans_info.setInfo(line,fileName,lineNum);
        
        //update Time and cargo graph.
        addEdges(rootPortName, lastPortName);
        
        //set current port leaving date
        trans_info.outBoundDate.setDate(trans_info.outBoundDateStr);
        
        //update\add port.
        updateRecvPort();
        
        //update root outbound deliveries.
        updateRootPort(rootPortName, RootOutBoundDate);
        
        //next line toread.
        lineNum++;
        //last port is currently visited port.
        lastPortName=trans_info.inBoundPortName;
    }while(getline(inputFile, line));
}

// check the input file for mistakes
void Clerk::verifyInputFile(string fileName){
    ifstream inputFile{fileName};
    if (inputFile.fail())
        throw OpenFileException::getExcept(fileName, 0);
    
    string line,tokken;
    bool failed=false;
    
    string rootPort;
    Date lastPortDate,outBoundPortDate,inBoundPortDate;
    int enteringCargo,lineNumber=0;
    
    while(getline(inputFile,line)){
        lineNumber++;
        int numberOfArg=0;
        istringstream iss(line);
        
        while(getline(iss,tokken,',')){
            numberOfArg++;
            switch (numberOfArg) {
                case 1:	// check port
                    if(tokken.find_first_not_of(ALPHA)!=tokken.npos)
                        failed=true;
                    else{// check if port is the same as root port
                        if(lineNumber==1)
                            rootPort = tokken;
                        else
                            if(tokken == rootPort)
                                failed = true;
                    }
                    break;
                case 2: // check inbound date (in case of first line then outbound)
                    if(lineNumber==1){
                        if(!lastPortDate.setDate(tokken))
                            failed=true;
                    }else{
                        if(!inBoundPortDate.setDate(tokken))
                            failed=true;
                    }
                    break;
                case 3:	// check amount of cargo
                    if(lineNumber==1 || tokken.find_first_not_of(NUMBERS)!=tokken.npos)
                        failed = true;
                    else{
                        enteringCargo = stoi(tokken);
                        if(enteringCargo<0)
                            failed = true;
                    }
                    break;
                case 4:	// check outboudnd date
                    if(lineNumber==1 || !outBoundPortDate.setDate(tokken))
                        failed=true;
                    break;
                default:	// if there are more the 4 argumets
                    failed = true;
                    break;
            }
        }
        if(!failed && lineNumber>1){// check if date is correct
            if(inBoundPortDate < lastPortDate || outBoundPortDate < inBoundPortDate)
                failed = true;
            else
                lastPortDate = outBoundPortDate;
        }
        
        if(failed)// problem has occured
            throw InvalidInputException::getExcept(fileName, lineNumber);
    }
    inputFile.close();
}



//treat first line, root port.
Date Clerk::handleFirstLine(string & firstLine, string fileName,string &portName){
    
    //prepare stringstream.
    stringstream ss(firstLine);
    
    //root name and outboundName.
    string line, outBoundportName, outBoundDate;
    Date dateOfDelivery;
    int lineNum=1;
    
    //handle first line
    getline(ss,outBoundportName , ',');
    if (outBoundportName.find_first_not_of(ALPHA)!=outBoundportName.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    //read outbound date.
    getline(ss,outBoundDate , ',');
    if (outBoundDate.find_first_not_of(DATE)!=outBoundDate.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    //create delivery information and add to port.
    dateOfDelivery.setDate(outBoundDate);
    Delivery outBoundDelivery{dateOfDelivery,0};
    
    
    // need to check if exist. if exist just need to add the outbound
    unordered_map<string ,Port >::iterator it= portsMap.find(outBoundportName);
    if (it!=portsMap.end())
    {
        (it->second).addOutDelivery(outBoundDelivery);
    }else
    {
        Port outBoundPort{outBoundportName}; //create outbound port.
        outBoundPort.addOutDelivery(outBoundDelivery);
        portsMap.emplace(outBoundportName,Port{outBoundPort});
    }
    
    portName=outBoundportName;
    return dateOfDelivery;
}



//set the info of current transaction.
void Clerk::Transaction_Info::setInfo(string line, string fileName, int lineNum){
    /*
     read portname, inbound date, cargo amount and outbound date.
     */
    istringstream iss{line};
    
    getline(iss,inBoundPortName,',');
    if (inBoundPortName.find_first_not_of(ALPHA)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, inBoundDateStr, ',');
    if (inBoundDateStr.find_first_not_of(DATE)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, cargoStr, ',');
    if (cargoStr.find_first_not_of(NUMBERS)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    getline(iss, outBoundDateStr, ',');
    if (outBoundDateStr.find_first_not_of(DATE)!=line.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    
    inBoundDate.setDate(inBoundDateStr);
    cargoAmount=stoi(cargoStr);
    
    
}


//clerk create new time and cargo edges and add them.
void Clerk::addEdges(string rootPort, string lastPort){
    
    //create a new TimeEdge. from lastPort to currentPort (held in trans_info).
    shared_ptr<Edge> newTimeEdge{new EdgeTime{(trans_info.inBoundDate)-(trans_info.outBoundDate)
        ,trans_info.inBoundPortName}};
    //add time edge to Time Graph.
    addNewEdge(lastPort, newTimeEdge,timeEdgesMap);
    
    
    //create new Cargo Edge.
    shared_ptr<Edge> cargoEdge{new EdgeCargo{trans_info.cargoAmount,trans_info.inBoundPortName}};
    //add cargo edge to Cargo Graph
    addNewEdge(rootPort, cargoEdge,cargoEdgesMap);
}


//add a single edge to a given graph.
void Clerk::addNewEdge(string portName, shared_ptr<Edge> newEdge,unordered_map<string,Edges> &graph )
{
    unordered_map<string,Edges>::iterator it;
    
    //check if port exist.
    it=graph.find(portName);
    if (it!=graph.end()){
        //if port exist check in Edges Vector for Edge. if does update, else push back.
        for (shared_ptr<Edge> spE : it->second){
            if (*newEdge==*spE){
                (*spE).updateEdge(*newEdge);
                return;
            }
        }
        it->second.push_back(newEdge);
    }else{
        //create a new <Port,Edges> pair and add edge.
        Edges v;
        v.push_back(newEdge);
        graph.emplace(portName,v);
    }
}



//update
void Clerk::updateRecvPort()
{
    Delivery inboundDelivery{trans_info.inBoundDate,trans_info.cargoAmount};
    unordered_map<string, Port>::iterator it;
    it=portsMap.find(trans_info.inBoundPortName);
    if (it!=portsMap.end())
        it->second.addInDelivery(inboundDelivery);
    Port current{trans_info.inBoundPortName};
    current.addInDelivery(inboundDelivery);
    portsMap.emplace(trans_info.inBoundPortName,current);
}


//update root port with adition Cargo.
void Clerk::updateRootPort(string rootPortName, Date rootOutBound)
{
    Delivery rootOutDelivery{rootOutBound,trans_info.cargoAmount};
    unordered_map<string, Port>::iterator it=portsMap.find(rootPortName);
    (it->second).addOutDelivery(rootOutDelivery);
    
}




/* query functions */

/* print to screen all out bound ports and the time to get to them */
void Clerk::outboundQuery(string port){
    /* check  if port exist */
    unordered_map<string,Edges>::iterator it = timeEdgesMap.find(port);
    if(it==timeEdgesMap.end()){
        cerr << port << ": does not exist in the database." << endl;
        return;
    }
    
    /* get all the outgoing edges from the port */
    Edges E = it->second;
    
    /* print all the outgping ports */
    if(E.size() < 1)
        cout << port << ": no outbound ports" << endl;
    else
        printPort(cout,E);
}

/* print all the ports entering to the port */
void Clerk::inboundQuery(string port){
    bool hasInbound=false;
    
    // getting the map iterator. checking all the vertices in the map
    unordered_map<string,Edges>::iterator mapIter = timeEdgesMap.begin();
    unordered_map<string,Edges>::iterator mapIterEnd = timeEdgesMap.end();
    
    for (; mapIter!= mapIterEnd; ++mapIter) {
        
        // get all the edges that belong to a certain vertex
        Edges E = mapIter->second;
        
        // checking all the edges in the vertex
        Edges::iterator edgesIter = E.begin();
        Edges::iterator edgesIterEnd = E.end();
        for (; edgesIter != edgesIterEnd; ++edgesIter) {
            Edge* e = edgesIter->get();
            
            // if edge is pointing to the entered vertex
            if(e->getDestination()==port){
                hasInbound=true;
                cout << mapIter->first << ", " << e->getWeight() << endl;
            }
        }
    }
    
    if(!hasInbound)
        cout << port << ": no inbound ports" << endl;
}


// calculating the number of containers at a given port in a given time
void Clerk::balance(string port,string date){
    // get the port and check validity
    unordered_map<string,Port>::iterator it = portsMap.find(port);
    if(it == portsMap.end()){
        cerr << port << " port does not exist in the database" << endl;
        return;
    }
    // get the date and check validity
    Date d;
    if (!d.setDate(date)){
        cerr<<"Invalid Date"<<endl;
        return;
    }
    // get the sum
    cout << it->second.calculateAmountOfContainers(d) << endl;
    
}


void Clerk::printPort(ostream& out,Edges& E){
    // print all given edges
    for_each(E.begin(),E.end(),\
             [&](shared_ptr<Edge> e){\
                 out << e->getDestination() << ", " << e->getWeight() << endl;\
             });
    
}


void Clerk::printGraph(ostream& out,string type,unordered_map<string,Edges>& map){
    
    unordered_map<string,Edges>::iterator mapIter = map.begin();
    unordered_map<string,Edges>::iterator mapIterEnd = map.end();
    
    out<<type<<" graph"<<":"<<endl;
    // for all vertices
    for (; mapIter!= mapIterEnd; ++mapIter) {
        // get all the edges that belong to a certain vertex
        Edges E = mapIter->second;
        out << mapIter->first << "-> ";
        printPort(out,E);
        out<<endl;
    }
}

// print all the records to a file
void Clerk::print(){
    // open file and check validity
    ofstream output(outputFile);
    if(!output.is_open()){
        cerr << "ERROR opening/reading the specified file." << endl;
        return;
    }
    
    output<<endl;
    printGraph(output,"Time",timeEdgesMap);
    output<<endl<<"----------------"<<endl<<endl;
    printGraph(output,"Cargo",cargoEdgesMap);
}


