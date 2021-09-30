//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_VALIDATOR_H
#define A89_915_NEDELCU_ALEXANDRU_VALIDATOR_H


#include "VirtualValidator.h"

class Validator : public VirtualValidator {
public:
    Validator();

    void validate(const Event& event);

    void validate(const Date& date);

    /**
     * An event used to perform a CRUD operation on the repository is called special event.
     * It only has one initialized attribute, which is its ID.
     * @param event : a special event
     */
    void validateSpecialEvent(const Event& event);
};


#endif //A89_915_NEDELCU_ALEXANDRU_VALIDATOR_H
