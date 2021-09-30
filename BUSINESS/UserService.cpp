//
// Created by Alex Nedelcu on 27.03.2021.
//

#include "UserService.h"

UserService::UserService(VirtualRepository<Event>* userRepository, Validator* validator, const std::string& persistenceOption)
        : m_persistenceOption{persistenceOption},
          m_userRepository{userRepository},
          m_validator{validator} {}

void UserService::addEvent(const Event& newEvent) {
    m_validator->validate(newEvent);
    m_userRepository->add(newEvent);
}

void UserService::removeEvent(int eventID) {
    Event specialEvent{eventID};
    m_validator->validateSpecialEvent(specialEvent);
    m_userRepository->remove(specialEvent);
}

void UserService::incrementParticipantsNumber(int eventID) {
    const Event& targetEvent = m_userRepository->get(Event{eventID});
    Event updatedEvent{targetEvent.getID(), targetEvent.getTitle(), targetEvent.getDescription(), targetEvent.getDate(),
                       targetEvent.getTime(), targetEvent.getParticipantsNumber() + 1, targetEvent.getLink()};
    m_userRepository->update(updatedEvent);
}

std::vector<Event> UserService::getEventsWishlist() const {
    return m_userRepository->getAll();
}

bool UserService::displayWishlistGUI() {
    if (m_persistenceOption == "1" || m_persistenceOption == "2") {
        std::string filename = m_userRepository->getFilename();
        std::string systemCommand = "open " + filename;
        system(systemCommand.c_str());
        return true;
    } else {
        return false;
    }
}
