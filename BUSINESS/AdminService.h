//
// Created by Alex Nedelcu on 22.03.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_ADMIN_SERVICE_H
#define A89_915_NEDELCU_ALEXANDRU_ADMIN_SERVICE_H

#include "../VALIDATION/Validator.h"
#include "../DOMAIN/Event.h"
#include "../DOMAIN/Date.h"
#include "../PERSISTENCE/VirtualRepository.h"

class AdminService {

private:
    VirtualRepository<Event>* m_adminRepository;
    Validator* m_validator;

public:
    explicit AdminService(VirtualRepository<Event>* adminRepository, Validator* validator);

    void addEvent(int eventID, const std::string& title, const std::string& description,
                  const std::string& time, int participantsNumber, const std::string& link,
                  int eventDay, int eventMonth, int eventYear);

    Event removeEvent(int eventID);

    Event updateEvent(int eventID, const std::string& updatedTitle, const std::string& updatedDescription,
                     const std::string& updatedTime, int updatedParticipantsNumber, const std::string& updatedLink,
                     int updatedDay, int updatedMonth, int updatedYear);

    bool checkEventExistence(int eventID) const;

    void incrementParticipantsNumber(int eventID);

    void decrementParticipantsNumber(int eventID);

    int getEventsNumber() const;

    std::vector<Event>& getAllEvents() const;

    std::vector<Event> getEventsByMonth(int month) const;

    std::vector<Event> getFutureEvents(int day, int month, int year) const;

    void populateEventsRepository();

    void writeToFile();
};

#endif //A89_915_NEDELCU_ALEXANDRU_ADMIN_SERVICE_H
