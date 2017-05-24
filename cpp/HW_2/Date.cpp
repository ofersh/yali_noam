/*
 * Date.cpp
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#include "Date.h"
#include <sstream>
#include <ctime>

using namespace std;


Date::Date():sum(),formatedDate("") {}

Date::Date(const Date& rhs):sum(rhs.sum),formatedDate(rhs.formatedDate){}

Date& Date::operator=(const Date& rhs){
	sum = rhs.sum;
	formatedDate = rhs.formatedDate;
	return *this;
}

/* calculate the minutes in the date */
void Date::setDate(int minute,int hour,int day,int month){
	sum = month*DAYS_IN_MONTH + day;
	sum = sum*HOURS_IN_DAY + hour;
	sum = sum*MINUTES_IN_HOURS + minute;

}

/* calculate the date from a readable format*/
bool Date::setDate(std::string& date){

	int min,h,d,mon;
	char trash;
	stringstream ss(date,ios::in | ios::out);

	ss >> d;
	if(ss.fail())
		return false;
	ss >> trash;
	if(trash!='/')
		return false;

	ss >> mon;
	if(ss.fail())
		return false;

	ss >> h;
	if(ss.fail())
		return false;
	ss >> trash;
	if(trash!=':')
		return false;

	ss >> min;
	if(ss.fail())
		return false;
	ss >> trash;
	if(!ss.fail())
		return false;

	setDate(min,h,d,mon);
	formatedDate = date;

	return true;
}

/* get the date in a readable format */
std::string Date::getDate(){
	return formatedDate;
}

/* compare between the dates */
bool Date::operator<(const Date& rhs){
	return sum < rhs.sum;
}

bool Date::operator>(const Date& rhs){
	return sum > rhs.sum;
}

int Date::operator-(const Date& rhs){
	return sum - rhs.sum;
}


Date::~Date() {}

