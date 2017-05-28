//
//  Graph.hpp
//  hw2
//
//  Created by Noam Stolero on 28/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <unordered_map>
#include <memory>
#include "Port.h"
#include "Edge.h"
#include <stdexcept>

using std::unordered_map;
using std::shared_ptr;

typedef vector<shared_ptr<Edge>> Edges;


class Graph {
    
public:
  
    
    void addEdges(Port* src, Port* dest);
    
    
    
private:
    unordered_map<string,shared_ptr<Port>> portsMap;
    unordered_map<string,Edges> edgesMap;
    
    
};



#endif /* Graph_hpp */
