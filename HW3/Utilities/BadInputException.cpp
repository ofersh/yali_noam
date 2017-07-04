/*
 * BadInputException.cpp
 *
 *  Created on: Jul 2, 2017
 *      Author: yali
 */

#include "BadInputException.h"

BadInputException::BadInputException(const char* whatArg):runtime_error(whatArg),err(whatArg) {}

BadInputException::~BadInputException() {}


