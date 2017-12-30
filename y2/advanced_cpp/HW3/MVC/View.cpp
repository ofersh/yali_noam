
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

View::~View() {}


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
    maxY= cell_size*map_size+origin.y-1;
    maxX=cell_size*map_size+origin.x-1;
    
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
    //check if object is in map.
    if (scaledPos.x>map_size-1 || scaledPos.x<0|| scaledPos.y>map_size-1 || scaledPos.y<0)
        return;

    name.resize(2);
    
    elements_row &er =map.at(scaledPos.y);
    elements_cell &cell=er.at(scaledPos.x);
    cell.push_back(name);
}

// return scaled postition of enterd point.
Point View::scale(Point cord)const
{
    Point fromOrigin= Point(cord.x-origin.x, cord.y-origin.y);
    Point scaled=Point(fromOrigin.x/cell_size,fromOrigin.y/cell_size);
    return Point(static_cast<int>(scaled.x),static_cast<int>(scaled.y));
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
void View::pan(double x, double y)
{
    if (origin.x==x && origin.y == y)
        return;
    origin.x=x;
    origin.y=y;
    init();
}


//print the map of all the elements.
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


// update
void View::updatePosition(string name,Point oldElemPos,Point newElemPos){

	Point oldPosOnMap = scale(oldElemPos);
	int oldX = oldPosOnMap.x,oldY = oldPosOnMap.y;
    if (oldX<0 || oldY<0 )
        return;
    
	elements_cell &cell = map[oldY][oldX];

    if (!cell.empty())
        cell.erase(find(cell.begin(),cell.end(),name));
	place(newElemPos,name);
}





