/*
* Main.cpp
 *
 *  Created on: May 24, 2017
 *      Author: yali
 */

#include <iostream>
#include "Delivery.h"

using namespace std;



int main(){
	Date d1,d2;
	string s1 = "12/09 11:05";
	string s2 = "12/09 11:07";

	if(!d1.setDate(s1)){
		cout << "calculating d1 failed" << endl;
		return 0;
	}
	if(!d2.setDate(s2)){
		cout << "calculating d1 failed" << endl;
		return 0;
	}
	if(d2<d1)
		cout << "right" << endl;
	else
		cout << "wrong" << endl;
	cout << d2-d1 << endl;
	return 0;
}


