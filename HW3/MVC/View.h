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
#include <map>
#include "../Elements/MarineElement.h"
#include <string>
#include <memory>

using std::pair;
using std::map;
using std::string;
using std::weak_ptr;

class View {
private:
    
    // Default Values.
    const static int MIN_SIZE=6;
    const static int MAX_SIZE=30;
    const static int DEFAULT_SIZE=25;
    
    Point origin;
    int cell_size;  //for scaling.
    int maxY;   //last visible y point.
    int maxX;   //last visible x point.
    
    
    // Holding map, sorted pair by y, and then x. values needs to be size 2 string.
    map<Point,string> Map;
    
    //calculate vertex.
    Point scale(Point cord)const;
    
    //place new element in map.
    void place(weak_ptr<Marine_Element> elem);
    
public:
	View();
	virtual ~View();
    
    
    void _default();
    void size(unsigned int size);
    void zoom(unsigned int ratio);
    void pan(unsigned int x, unsigned int y);
    void show()const;
    
    
};

#endif /* VIEW_H_ */
