
#include "BadInputException.h"

BadInputException::BadInputException(const char* whatArg):runtime_error(whatArg),err(whatArg) {}

BadInputException::~BadInputException() {}


