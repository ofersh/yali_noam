/*
 * View.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef MVC_VIEW_H_
#define MVC_VIEW_H_

#include <utility>
#include <vector>
#include "../Elements/MarineElement.h"
#include <string>
#include <memory>

using std::pair;
using std::vector;
using std::string;
using std::weak_ptr;

using elements_cell=vector<string>;
using elements_row=vector<elements_cell>;
using elements_map=vector<elements_row>;

class View {
private:
    
    // Default Values.
    const static int MIN_SIZE=6;
    const static int MAX_SIZE=30;
    const static int DEFAULT_MAP_SIZE=25;
    const static int DEFAULT_CELL_SIZE=2;
    const static string EMPTY_CELL;
    
    Point origin;
    double cell_size;  //for scaling.
    int map_size;
    int maxY;   //last visible y point.
    int maxX;   //last visible x point.
    
    elements_map map;
    
    
    
    //calculate vertex.
    Point scale(Point cord)const;
    
    //init the View.
    void init();
    void map_all_elements();
    
    //place new element in map.
    void place(Point real_pos, string name);
    
public:
	View();
	~View();
    
    
    void _default();
    void size(unsigned int size);
    void zoom(double ratio);
    void pan(unsigned int x, unsigned int y);
    void show()const;
    void refresh(){init();};
    
    void updatePosition(string name,Point oldPos,Point newPos);
    
    
    
    class IllegalMapSizeException : public runtime_error
    {
    public:
        IllegalMapSizeException(string what)        :runtime_error{what}{};
    };

};

#endif /* VIEW_H_ */
