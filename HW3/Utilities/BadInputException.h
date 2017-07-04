/*
 * BadInputException.h
 *
 *  Created on: Jul 2, 2017
 *      Author: yali
 */

#ifndef UTILITIES_BADINPUTEXCEPTION_H_
#define UTILITIES_BADINPUTEXCEPTION_H_

#include <stdexcept>
#include <string>

class BadInputException: public std::runtime_error {
public:
	BadInputException(const char*);
	~BadInputException();
	std::string err;
};

#endif /* BADINPUTEXCEPTION_H_ */
