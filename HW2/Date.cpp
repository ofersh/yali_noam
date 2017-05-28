/*
 * Date.cpp
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#include "Date.h"
#include <sstream>
#include <ctime>
#include <iostream>
using namespace std;


/* calculate the minutes in the date */
void Date::setDate(int minute,int hour,int day,int month){
	sum = (month)*DAYS_IN_MONTH + day;
	sum = sum*HOURS_IN_DAY + hour;
	sum = sum*MINUTES_IN_HOURS + minute;

}

/* calculate the date from a readable format*/
bool Date::setDate(string& date){
	tm t;
	if (strptime(date.c_str(),"%d/%m %H:%M",&t)){
		setDate(t.tm_min,t.tm_hour,t.tm_mday,t.tm_mon);
		formatedDate=date;
		return true;
	}
	return false;
}

/* get the date in a readable format */
std::string Date::getDate(){
	return formatedDate;
}

/* compare between the dates */
bool Date::operator<(const Date& rhs)const{
	return sum < rhs.sum;
}

bool Date::operator>(const Date& rhs)const{
	return sum > rhs.sum;
}

bool Date::operator==(const Date & rhs)const{
    return sum==rhs.sum;
}

int Date::operator-(const Date& rhs)const{
	return sum - rhs.sum;
}


Date::~Date() {}

