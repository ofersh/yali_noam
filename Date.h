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

public:
	/* default constructor and copy constructor  needed
	Date();
	Date(const Date&);
	Date(const Date&&);
	Date& operator=(const Date&);
	Date& operator=(const Date&&);
*/
	bool setDate(std::string&);
	std::string getDate();

	bool operator<(const Date&);
	bool operator>(const Date&);
	int operator-(const Date&);

	virtual ~Date();

private:
	int sum;
	std::string formatedDate;

	static const int DAYS_IN_MONTH=30;
	static const int HOURS_IN_DAY=24;
	static const int MINUTES_IN_HOURS=60;

	void setDate(int,int,int,int);

};

#endif /* DATE_H_ */
