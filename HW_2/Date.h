/*
 * Date.h
 *
 *  Created on: May 22, 2017
 *      Author: yali
 */

#ifndef DATE_H_
#define DATE_H_

#include <string>


class Date {
private:
	int sum;
	std::string formatedDate;

	const int DAYS_IN_MONTH=30;
	const int HOURS_IN_DAY=24;
	const int MINUTES_IN_HOURS=60;

	void setDate(int,int,int,int);

public:
	Date();
	Date(const Date&);
	Date& operator=(const Date&);

	bool setDate(std::string&);
	std::string getDate();

	bool operator<(const Date&);
	bool operator>(const Date&);
	int operator-(const Date&);

	virtual ~Date();
};

#endif /* DATE_H_ */
