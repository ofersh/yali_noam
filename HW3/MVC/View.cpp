/*
 * View.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#include "View.h"
#include <iostream>

View::View() {
	// TODO Auto-generated constructor stub

}

View::~View() {
	// TODO Auto-generated destructor stub
}




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
