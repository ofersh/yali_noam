/*
 * View.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "View.h"
#include "Model.h"
#include "../Elements/MarineElement.h"
#include <iostream>
#include <algorithm>

const string View::EMPTY_CELL{".."};

View::View(): origin(0,0), cell_size(DEFAULT_CELL_SIZE), map_size(DEFAULT_MAP_SIZE),maxY(DEFAULT_MAP_SIZE),maxX(DEFAULT_MAP_SIZE)
{
    init();
}

View::~View() {
    // TODO Auto-generated destructor stub
}


// initailized the map regarding its properties.
void View::init()
{
    //init destroys the map and rebuild it.
    map.clear();
    map.resize(map_size);
    for (elements_row& row: map)
    {
        row.resize(map_size); //make a row of empty vectors.
    }
    maxY=cell_size*map_size+origin.y;
    maxX=cell_size*map_size+origin.x;
    
    map_all_elements();
}


//map each elemnt of Model.
void View::map_all_elements()
{
    Model& m=Model::getModel();
    const vector<shared_ptr<Marine_Element>>& elem_list=m.get_element_list();
    
    for (const weak_ptr<Marine_Element>& wme: elem_list)
    {
        place(wme.lock()->getPosition(),wme.lock()->getName());
    }
}


//place a new element in map.
void View::place(Point real_pos, string name)
{
    
    //prepare new point and string.
    Point scaledPos=scale(real_pos);
    if (scaledPos.x> map_size-1 || scaledPos.y>map_size-1)
        return;
    name.resize(2);
    
    elements_row &er =map.at(scaledPos.y);
    elements_cell &cell=er.at(scaledPos.x);
    cell.push_back(name);
}

// return scaled postition of enterd point.
Point View::scale(Point cord)const
{
    return Point(static_cast<int>(cord.x/cell_size),static_cast<int>(cord.y/cell_size));
}


//set all view option to default.
void View::_default()
{
    origin.x=0;
    origin.y=0;
    cell_size=DEFAULT_CELL_SIZE;
    map_size=DEFAULT_MAP_SIZE;
    init();
}


//change the size of the map.
void View::size(unsigned int size)
{
    if (size>MAX_SIZE || size < MIN_SIZE)
        throw IllegalMapSizeException{"Must be between 6 and 30"};
    map_size=size;
    init();
}


//change the ratio of the cell to real positon.
void View::zoom(double ratio)
{
    if (cell_size==ratio)
        return;
    cell_size=ratio;
    init();
}

//change the origin of the map.
void View::pan(unsigned int x, unsigned int y)
{
    if (origin.x==x && origin.y == y)
        return;
    origin.x=x;
    origin.y=y;
}


//print the map of all the elemtns.
void View::show()const
{
    
    //going from top to bottom.
    auto row_it_begin=map.crbegin(), row_it_end=map.crend();
    for (; row_it_begin!=row_it_end; row_it_begin++)
    {
        for (const elements_cell &cell: *row_it_begin)
        {
            if (cell.empty())
                cout<<".. ";
            else{
                cout<<cell.front()<<" ";
            }
        }
        cout<<endl;
    }

    
}


void View::updatePosition(string name,Point oldElemPos,Point newElemPos){

	Point oldPosOnMap = scale(oldElemPos);
	Point newPosOnMap = scale(newElemPos);
	int oldX = oldPosOnMap.x,oldY = oldPosOnMap.y ,newX = newPosOnMap.x,newY = newPosOnMap.y;

	place(newElemPos,name);
}





