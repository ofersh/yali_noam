//
//  Graph.cpp
//  hw2
//
//  Created by Noam Stolero on 28/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#include "Graph.hpp"




void Graph::addEdges(Port* src , Port* dest){
    
    //adding date edge from last port to current.
    unordered_map<string,Edges>::iterator it;
    
    
    //create a new TimeEdge. from lastPort to currentPort (held in trans_info).
    shared_ptr<Edge> newTimeEdge{new EdgeTime{(trans_info.inBoundDate)-(trans_info.outBoundDate)
        ,trans_info.inBoundPortName}};
    
    //first find if Port exist in map exist
    it=timeEdgesMap.find(lastPort);
    if (it!=timeEdgesMap.end()){
        //if port exist check in Edges Vector for Edge. if does update, else push back.
        Edges::iterator exist=find(it->second.begin(), it->second.end(), newTimeEdge);
        if (exist!=it->second.end())
            (*exist)->updateEdge(*newTimeEdge);
        else
            it->second.push_back(newTimeEdge);
    }else{
        //create a new <Port,Edges> pair and add edge.
        Edges v;
        v.push_back(newTimeEdge);
        timeEdgesMap.emplace(lastPort,v);
    }
    shared_ptr<Edge> timeEdge{newTimeEdge};
    
    
    shared_ptr<Edge> cargoEdge{new EdgeCargo{trans_info.cargoAmount,trans_info.inBoundPortName}};
    
    it=cargoEdgesMap.find(rootPort);
    if(it!=timeEdgesMap.end()){
        //TODO: check if edge does exist, if yes invoke update edge.
        (it->second).push_back(cargoEdge);
    }else{
        Edges v;
        v.push_back(cargoEdge);
        timeEdgesMap.emplace(lastPort,v);
    }
