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
	int sum;
	std::string formatedDate;

	void setDate(int,int,int,int);


public:
	Date();
	Date(const Date&);
	Date& operator=(const Date&);

	bool setDate(std::string&);
	std::string getDate();

	bool operator<(const Date&);
	bool operator>(const Date&);

	virtual ~Date();
};

#endif /* DATE_H_ */
