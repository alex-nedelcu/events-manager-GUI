//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_REPOSITORYEXCEPTION_H
#define A89_915_NEDELCU_ALEXANDRU_REPOSITORYEXCEPTION_H


#include "BaseException.h"

class RepositoryException : public BaseException {
public:
    explicit RepositoryException(const std::string& errorMessage);
};


#endif //A89_915_NEDELCU_ALEXANDRU_REPOSITORYEXCEPTION_H
