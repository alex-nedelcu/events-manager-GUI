//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_BASEEXCEPTION_H
#define A89_915_NEDELCU_ALEXANDRU_BASEEXCEPTION_H


#include <exception>
#include <string>

class BaseException : public std::exception {
protected:
    std::string m_errorMessage;

public:
    explicit BaseException(const std::string& errorMessage);

    const std::string& getErrorMessage() const;
};


#endif //A89_915_NEDELCU_ALEXANDRU_BASEEXCEPTION_H
