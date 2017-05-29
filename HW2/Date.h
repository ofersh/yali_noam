/*
 * Date.h
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#ifndef DATE_H_
#define DATE_H_

#include <string>


using std::string;

class Date {

public:
	Date()=default;
	Date(const Date&)=default;
	Date(Date&&)=default;
	Date& operator=(const Date&)=default;
	Date& operator=(Date&&)=default;

	bool setDate(string&);
	string getDate();

	// operators for Date
	bool operator<(const Date&)const;
	bool operator>(const Date&)const;
    bool operator==(const Date&)const;
	int operator-(const Date&)const;

	virtual ~Date();

private:
	int sum=0;
	string formatedDate;

	static const int DAYS_IN_MONTH=30;
	static const int HOURS_IN_DAY=24;
	static const int MINUTES_IN_HOURS=60;

	// calculate the sum of the date
	void setDate(int,int,int,int);

};

#endif /* DATE_H_ */
