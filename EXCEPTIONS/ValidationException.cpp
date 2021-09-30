//
// Created by Alex Nedelcu on 10.04.2021.
//

#include "ValidationException.h"

ValidationException::ValidationException(const std::string& errorMessage) : BaseException(errorMessage) {
}
