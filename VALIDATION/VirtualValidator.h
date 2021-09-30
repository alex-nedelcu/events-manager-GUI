//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_VIRTUALVALIDATOR_H
#define A89_915_NEDELCU_ALEXANDRU_VIRTUALVALIDATOR_H

#include "../DOMAIN/Date.h"
#include "../DOMAIN/Event.h"

class VirtualValidator {
public:
    virtual void validate(const Event& event) = 0;

    virtual void validate(const Date& date) = 0;
};

#endif //A89_915_NEDELCU_ALEXANDRU_VIRTUALVALIDATOR_H
