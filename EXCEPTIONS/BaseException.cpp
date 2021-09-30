//
// Created by Alex Nedelcu on 10.04.2021.
//

#include "BaseException.h"

BaseException::BaseException(const std::string& errorMessage) : std::exception(), m_errorMessage{errorMessage} {
}

const std::string& BaseException::getErrorMessage() const {
    return m_errorMessage;
}
