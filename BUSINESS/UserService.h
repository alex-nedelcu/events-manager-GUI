//
// Created by Alex Nedelcu on 27.03.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_USER_SERVICE_H
#define A89_915_NEDELCU_ALEXANDRU_USER_SERVICE_H

#include "../VALIDATION/Validator.h"
#include "../DOMAIN/Event.h"
#include "../DOMAIN/Date.h"
#include "../PERSISTENCE/VirtualRepository.h"

class UserService {
private:
    VirtualRepository<Event>* m_userRepository;
    Validator* m_validator;
    const std::string& m_persistenceOption;

public:
    explicit UserService(VirtualRepository<Event>* userRepository, Validator* validator, const std::string& persistenceOption);

    void addEvent(const Event& newEvent);

    void removeEvent(int eventID);

    void incrementParticipantsNumber(int eventID);

    std::vector<Event> getEventsWishlist() const;

    bool displayWishlistGUI();
};

#endif //A89_915_NEDELCU_ALEXANDRU_USER_SERVICE_H
