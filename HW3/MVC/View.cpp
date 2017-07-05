/*
 * View.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "View.h"
#include <iostream>

View::View():cell_size(DEFAULT_CELL_SIZE),map_size(DEFAULT_MAP_SIZE)
{
    init();
}

View::~View() {
	// TODO Auto-generated destructor stub
}


// initailized the map regarding its properties.
void View::init()
{
    if (map.max_size())
    map.resize(map_size);
    for (vector<string> row: map)
    {
        row.resize(map_size);
    }
    maxY=cell_size*map_size+origin.y;
    maxX=cell_size*map_size+origin.x;
    
}


// return scaled postition of enterd point.
Point View::scale(Point cord)const
{
    return Point(cord.x/cell_size,cord.y/cell_size);
}


//set all view option to default.
void View::_default()
{
    cout<<"View::_default"<<endl;
}


void View::size(unsigned int size)
{
    cout<<"View::size()"<<endl;
}

void View::zoom(unsigned int ratio)
{
    cout<<"View::zoom"<<endl;
}

void View::pan(unsigned int x, unsigned int y)
{
    cout<<"View::pan"<<endl;
}

void View::show()const
{
    cout<<"View::show"<<endl;
}
