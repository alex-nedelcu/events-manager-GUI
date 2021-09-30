//
// Created by Alex Nedelcu on 22.03.2021.
//

#include "AdminService.h"

AdminService::AdminService(VirtualRepository<Event>* adminRepository, Validator* validator)
        : m_adminRepository{adminRepository},
          m_validator{validator} {}

void AdminService::addEvent(int eventID, const std::string& title, const std::string& description,
                            const std::string& time, int participantsNumber, const std::string& link,
                            int eventDay, int eventMonth, int eventYear) {
    Date eventDate = Date(eventDay, eventMonth, eventYear);
    Event newEvent = Event(eventID, title, description, eventDate, time, participantsNumber, link);
    m_validator->validate(newEvent);
    m_adminRepository->add(newEvent);
}

Event AdminService::removeEvent(int eventID) {
    Event specialEvent{eventID};
    m_validator->validateSpecialEvent(specialEvent);
    Event removedEvent = m_adminRepository->get(specialEvent);
    m_adminRepository->remove(specialEvent);
    return removedEvent;
}

Event AdminService::updateEvent(int eventID, const std::string& updatedTitle, const std::string& updatedDescription,
                                const std::string& updatedTime, int updatedParticipantsNumber,
                                const std::string& updatedLink, int updatedDay, int updatedMonth, int updatedYear) {
    Date updatedDate = Date(updatedDay, updatedMonth, updatedYear);
    Event updatedEvent = Event(eventID, updatedTitle, updatedDescription, updatedDate, updatedTime, updatedParticipantsNumber, updatedLink);
    m_validator->validate(updatedEvent);
    Event initialEvent = m_adminRepository->get(updatedEvent);
    m_adminRepository->update(updatedEvent);
    return initialEvent;
}

bool AdminService::checkEventExistence(int eventID) const {
    Event specialEvent{eventID};
    m_validator->validateSpecialEvent(specialEvent);
    return m_adminRepository->checkExistence(specialEvent);
}

void AdminService::incrementParticipantsNumber(int eventID) {
    const Event& targetEvent = m_adminRepository->get(Event{eventID});
    Event updatedEvent{targetEvent.getID(), targetEvent.getTitle(), targetEvent.getDescription(), targetEvent.getDate(),
                       targetEvent.getTime(), targetEvent.getParticipantsNumber() + 1, targetEvent.getLink()};
    m_validator->validate(updatedEvent);
    m_adminRepository->update(updatedEvent);
}

void AdminService::decrementParticipantsNumber(int eventID) {
    const Event& targetEvent = m_adminRepository->get(Event{eventID});
    Event updatedEvent{targetEvent.getID(), targetEvent.getTitle(), targetEvent.getDescription(), targetEvent.getDate(),
                       targetEvent.getTime(), targetEvent.getParticipantsNumber() - 1, targetEvent.getLink()};
    m_validator->validate(updatedEvent);
    m_adminRepository->update(updatedEvent);
}

int AdminService::getEventsNumber() const {
    return m_adminRepository->size();
}

std::vector<Event>& AdminService::getAllEvents() const {
    return m_adminRepository->getAll();
}

std::vector<Event> AdminService::getEventsByMonth(int month) const {
    std::vector<Event> events = m_adminRepository->getAll();
    std::vector<Event> searchedEvents{};

    auto monthCondition = [month](auto event) {return event.getDate().getMonth() == month;};
    std::copy_if(events.begin(), events.end(), std::back_inserter(searchedEvents), monthCondition);

    std::sort(searchedEvents.begin(), searchedEvents.end(), [](const auto e1, const auto e2) {
        return e2.getDate() > e1.getDate();
    });

    return searchedEvents;
}

std::vector<Event> AdminService::getFutureEvents(int day, int month, int year) const {
    std::vector<Event> events = m_adminRepository->getAll();
    std::vector<Event> searchedEvents;

    Date targetDate = Date(day, month, year);
    m_validator->validate(targetDate);

    auto futureCondition = [targetDate](auto event) {return (event.getDate() > targetDate || event.getDate() == targetDate);};
    std::copy_if(events.begin(), events.end(), std::back_inserter(searchedEvents), futureCondition);

    std::sort(searchedEvents.begin(), searchedEvents.end(), [](const auto e1, const auto e2) {
        return e2.getDate() > e1.getDate();
    });

    return searchedEvents;
}

void AdminService::populateEventsRepository() {
    m_adminRepository->clearRepository();
    addEvent(1, "Neversea festival", "summer music festival in Constanta", "19:00", 46000, "https://neversea.com", 8, 7, 2021);
    addEvent(2, "Untold festival", "summer music festival in Cluj-Napoca", "17:30", 53000, "https://untold.com", 5, 8, 2021);
    addEvent(3, "Red Cross first-aid course", "course held by the Red Cross Training Services", "10:15", 20, "https://www.redcross.org/take-a-class/first-aid/first-aid-training", 19, 4, 2021);
    addEvent(4, "Street food festival", "street food festival in the center of the town", "16:00", 2000, "https://streetfoodfestival.ro", 12, 4, 2021);
    addEvent(5, "Volunteering activity", "local forest cleanup", "9:45", 100, "https://www.unv.org", 28, 4, 2021);
}

void AdminService::writeToFile() {
    this->m_adminRepository->writeDataIntoFile();
}




