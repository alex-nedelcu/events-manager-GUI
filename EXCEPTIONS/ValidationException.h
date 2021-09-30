//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_VALIDATIONEXCEPTION_H
#define A89_915_NEDELCU_ALEXANDRU_VALIDATIONEXCEPTION_H


#include "BaseException.h"

class ValidationException : public BaseException {
public:
    explicit ValidationException(const std::string& errorMessage);
};


#endif //A89_915_NEDELCU_ALEXANDRU_VALIDATIONEXCEPTION_H
