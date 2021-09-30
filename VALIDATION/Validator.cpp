//
// Created by Alex Nedelcu on 10.04.2021.
//

#include <regex>
#include "../EXCEPTIONS/ValidationException.h"
#include "Validator.h"


void Validator::validate(const Event& event) {
    std::string errorMessage = "";

    if (event.getID() < 0)
        errorMessage += "Invalid ID: cannot be negative!\n";

    if (event.getTitle().empty())
        errorMessage += "Invalid title: cannot be empty!\n";

    if (event.getDescription().empty())
        errorMessage += "Invalid description: cannot be empty!\n";

    if (event.getParticipantsNumber() < 0)
        errorMessage += "Invalid number of participants: cannot be negative!\n";

    std::regex timePattern("[0-2]?[0-9]{1}:[0-5]{1}[0-9]{1}");
    if (!std::regex_match(event.getTime(), timePattern))
        errorMessage += "Invalid time format: must have the format <hh:mm>!\n";

    if (event.getLink().empty())
        errorMessage += "Invalid link: cannot be empty!\n";

    try {
        this->validate(event.getDate());
    } catch (const ValidationException& vex) {
        errorMessage += vex.getErrorMessage();
    }

    if (!errorMessage.empty())
        throw ValidationException{errorMessage};
}

void Validator::validate(const Date& date) {
    std::string errorMessage = "";

    if (date.getDay() < 0 || date.getDay() > 31)
        errorMessage += "Invalid day: must be an integer between 1 and 31!\n";

    if (date.getMonth() < 0 || date.getMonth() > 12)
        errorMessage += "Invalid month: must be an integer between 1 and 12!\n";

    if (date.getYear() < 0 || date.getYear() > 2500)
        errorMessage += "Invalid year: must be an integer between 0 and 2500!\n";

    if (!errorMessage.empty())
        throw ValidationException{errorMessage};
}

void Validator::validateSpecialEvent(const Event& event) {
    std::string errorMessage = "";

    if (event.getID() < 0)
        errorMessage += "Invalid ID: cannot be negative!\n";

    if (!errorMessage.empty())
        throw ValidationException{errorMessage};
}

Validator::Validator() : VirtualValidator() {
}


