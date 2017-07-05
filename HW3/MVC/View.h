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

class View {
private:
    
    // Default Values.
    const static int MIN_SIZE=6;
    const static int MAX_SIZE=30;
    const static int DEFAULT_MAP_SIZE=25;
    const static int DEFAULT_CELL_SIZE=2;
    
    Point origin;
    int cell_size;  //for scaling.
    int map_size;
    int maxY;   //last visible y point.
    int maxX;   //last visible x point.
    vector<vector<string>> map; //scaled map of elements.
    
    
    //calculate vertex.
    Point scale(Point cord)const;
    
    //init the View.
    void init();
    
    //place new element in map.
    void place(weak_ptr<Marine_Element> elem);
    
public:
	View();
	~View();
    
    
    void _default();
    void size(unsigned int size);
    void zoom(unsigned int ratio);
    void pan(unsigned int x, unsigned int y);
    void show()const;
    
    
    void updatePosition(string name,Point oldPos,Point newPos);


};

#endif /* VIEW_H_ */
