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

using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::stoi;



static const string ALPHA{"abcdefghijklmnopqrstuvwxyz\
    ABCDEFGHIJKLMNOPQRSTUVWXYZ "},\
    DATE{"0123456789:/ "},\
    NUMBERS{"0123456789"};


void Clerk::load(string fileName){
    
    ifstream inputFile{fileName};
    if (inputFile.fail())
        throw OpenFileException::getExcept(fileName, 0);
    
    string rootPortName;
    Date RootOutBoundDate=handleFirstLine(inputFile, fileName, rootPortName);
    Date OutBoundDate=RootOutBoundDate;
    //read line by line each port in the journey.
    string line, lastPortName=rootPortName;

    int lineNum=2;
    getline(inputFile, line);
    do{
        //read transaction data.
        trans_info.setInfo(line,fileName,lineNum);
        
        //update Time and cargo graph.
        addEdges(rootPortName, lastPortName);
        
        //set chrrent port leaving date
        OutBoundDate.setDate(trans_info.outBoundDateStr);
        
        //update\add port.
        updateRecvPort();
    
        //update root outbound deliveries.
        updateRootPort(rootPortName, RootOutBoundDate);
        
        lineNum++;
    }while(getline(inputFile, line));
    
}



Date Clerk::handleFirstLine(ifstream & inputFile, string fileName,string &portName){
    
    string line, outBoundportName, outBoundDate;
    Date dateOfDelivery;
    int lineNum=1;
    
    //handle first line
    getline(inputFile,outBoundportName , ',');
    if (outBoundportName.find_first_of(ALPHA)!=outBoundportName.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    Port outBoundPort{outBoundportName}; //create outbound port.
    //read outbound date.
    getline(inputFile,outBoundDate , ',');
    if (outBoundDate.find_first_of(DATE)!=outBoundDate.npos)
        throw InvalidInputException::getExcept(fileName, lineNum);
    
    //create delivery information and add to port.
    dateOfDelivery.setDate(outBoundDate);
    Delivery outBoundDelivery{dateOfDelivery,0};
    outBoundPort.addOutDelivery(outBoundDelivery);
    // need to check if exist. if exist just need to add the outbound
    portsMap.emplace(dateOfDelivery,new Port{outBoundPort});
    portName=outBoundportName;
    return dateOfDelivery;
}

void Clerk::Transaction_Info::setInfo(string line, string fileName, int lineNum){
    
    istringstream iss{line};
    string inBoundDateStr="" ,cargoStr="";
    
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

void Clerk::addEdges(string rootPort, string lastPort){

    //adding date edge from last port to current.
    timeEdgesMap.emplace(lastPort, \
    new EdgeTime{(trans_info.inBoundDate)-(trans_info.outBoundDate),trans_info.inBoundPortName});
    //adding cargoEdge from root to current.
    cargoEdgesMap.emplace(rootPort,new EdgeCargo{trans_info.cargoAmount,trans_info.inBoundPortName});
}


void Clerk::updateRecvPort(){
    
    Delivery inboundDelivery{trans_info.inBoundDate,trans_info.cargoAmount};

    unordered_map<string, Port>::iterator it;
    it=portsMap.find(trans_info.inBoundPortName);
    if (it!=portsMap.end())
        it->second.addInDelivery(inboundDelivery);
    
    Port current{trans_info.inBoundPortName};
    current.addInDelivery(inboundDelivery);
    portsMap.emplace(trans_info.inBoundPortName,current);
}


void Clerk::updateRootPort(string rootPortName, Date rootOutBound){
    
    Delivery rootOutDelivery{rootOutBound,trans_info.cargoAmount};
    unordered_map<string, Port>::iterator it=portsMap.find(rootPortName);
    (it->second).addOutDelivery(rootOutDelivery);
    
}







