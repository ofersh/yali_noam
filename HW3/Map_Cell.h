//
//  Map_Cell.hpp
//  hw3
//
//  Created by Noam Stolero on 28/06/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef Map_Cell_hpp
#define Map_Cell_hpp

#include <stdio.h>
#include <vector>
#include "MarineElement.h"
#include <memory>
#include <string>
#include <iostream>

using std::vector;
using std::weak_ptr;
using std::string;
using std::ostream;

class Map_Cell {
    
    static int size; //for scaling.
    static const string EMPTY_CELL;
    
    //each cell represent x+size,y+size dots.
    int startingX;
    int startingY;
    
    vector<weak_ptr<Marine_Element>> elem_in_cell;
    
    
public:
    
    
    Map_Cell(int size=2);
    
    
    
    
    void set_scale(int size);
    
    
    int getStartX()const;
    int getStartY()const;
    int getSize()const;
    
    
    bool isEmpty()const;
    

    //for printing cell.
    friend ostream & operator<<(ostream& out, const Map_Cell & cell ){
        if (!cell.isEmpty())
            out<<cell.elem_in_cell.front().lock();  //need to check.. i think only first element need to be printed.
        else
            out<<EMPTY_CELL;
        return out;
    };
    
    
    
    
};


#endif /* Map_Cell_hpp */
