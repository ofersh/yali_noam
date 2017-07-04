/*
 * BadInputException.h
 *
 *  Created on: Jul 2, 2017
 *      Author: yali
 */

#ifndef BADINPUTEXCEPTION_H_
#define BADINPUTEXCEPTION_H_

#include <stdexcept>

class BadInputException: public std::runtime_error {
public:
	BadInputException(const char*);
	~BadInputException();
};

#endif /* BADINPUTEXCEPTION_H_ */
