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
    for (elements_row row: map)
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
    
    for (weak_ptr<Marine_Element> wme: elem_list)
    {
        place(wme.lock()->getPosition(),wme.lock()->getName());
    }
}


//place a new element in map.
void View::place(Point real_pos, string name)
{
    if (real_pos.x>maxX || real_pos.y>maxY)
        return;
    
    //prepare new point and string.
    Point scaledPos=scale(real_pos);
    name.resize(2);
    
    vector<string> cell=map.at(scaledPos.x).at(scaledPos.y);
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


void View::updatePosition(string name,Point oldElemPos,Point newElemPos){

	Point oldPosOnMap = scale(oldElemPos);
	Point newPosOnMap = scale(newElemPos);
	int oldX = oldPosOnMap.x,oldY = oldPosOnMap.y ,newX = newPosOnMap.x,newY = newPosOnMap.y;

	place(newElemPos,name);
}





