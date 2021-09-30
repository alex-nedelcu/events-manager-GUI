//
// Created by Alex Nedelcu on 21.03.2021.
//

#include <vector>
#include <sstream>
#include "Event.h"

Event::Event() : m_ID{-1}, m_date{Date()}, m_participantsNumber{-1} {
}

Event::Event(int ID) : m_ID{ID}, m_date{Date()}, m_participantsNumber{-1} {
}

Event::Event(int ID, const std::string& title, const std::string& description, const Date& date, const std::string& time, int participantsNumber, const std::string& link)
        :
        m_ID{ID},
        m_title{title},
        m_description{description},
        m_date{date},
        m_participantsNumber{participantsNumber},
        m_time{time},
        m_link{link} {}

std::ostream& operator <<(std::ostream& outputStream, const Event& event) {
    outputStream << event.m_ID << "," << event.m_title << "," << event.m_description << "," << event.m_date.getDay() << ","
                 << event.m_date.getMonth() << "," << event.m_date.getYear() << "," << event.m_time << ","
                 << event.m_participantsNumber << "," << event.m_link;
    return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Event& event) {
    char separator;
    std::string line;

    std::getline(inputStream, line, '\n');
    if (line.find(';') != std::string::npos)
        separator = ';';
    else if (line.find(',') != std::string::npos)
        separator = ',';
    else separator = ' ';
    std::stringstream input(line);


    std::string stringID, stringDay, stringMonth, stringYear, stringParticipants;

    std::getline(input, stringID, separator);
    std::getline(input, event.m_title, separator);
    std::getline(input, event.m_description, separator);
    std::getline(input, stringDay, separator);
    std::getline(input, stringMonth, separator);
    std::getline(input, stringYear, separator);
    std::getline(input, event.m_time, separator);
    std::getline(input, stringParticipants, separator);
    std::getline(input, event.m_link, '\n');


    int ID = std::stoi(stringID);
    int day = std::stoi(stringDay);
    int month = std::stoi(stringMonth);
    int year = std::stoi(stringYear);
    int participantsNumber = std::stoi(stringParticipants);

    event.m_ID = ID;
    event.m_date = Date{day, month, year};
    event.m_participantsNumber = participantsNumber;

    return inputStream;
}

void Event::prettyPrint() const {
    std::cout << "ID: " << m_ID << std::endl;
    std::cout << "Title: " << m_title << std::endl;
    std::cout << "Description: " << m_description << std::endl;
    std::cout << "Number of participants: " << m_participantsNumber << std::endl;
    std::cout << "Date(dd/mm/yyyy): " << m_date.getDay() << "/" << m_date.getMonth() << "/" << m_date.getYear() << std::endl;
    std::cout << "Time: " << m_time << std::endl;
    std::cout << "Website: " << m_link << std::endl;
}

std::string Event::toStringEssentials() const {
    std::string eventAsString;
    std::string IDAsString = std::to_string(m_ID);
    std::string dayAsString = std::to_string(m_date.getDay());
    std::string monthAsString = std::to_string(m_date.getMonth());
    std::string yearAsString = std::to_string(m_date.getYear());
    std::string participantsAsString = std::to_string(m_participantsNumber);
    eventAsString = m_title + ": " + m_description;
    return eventAsString;
}

std::string Event::toStringComplete() const {
    std::string eventAsString;
    std::string IDAsString = std::to_string(m_ID);
    std::string dayAsString = std::to_string(m_date.getDay());
    std::string monthAsString = std::to_string(m_date.getMonth());
    std::string yearAsString = std::to_string(m_date.getYear());
    std::string participantsAsString = std::to_string(m_participantsNumber);
    eventAsString = "[" + IDAsString + "] " + m_title + " " + "(" + m_description + ")," + " " +
                    dayAsString + "/" + monthAsString + "/" + yearAsString + "," + " " + participantsAsString + " " +
                    "participants," + " " + m_time + ", " + m_link;
    return eventAsString;
}

void Event::setTitle(const std::string& newTitle) {
    m_title = newTitle;
}

void Event::setDescription(const std::string& newDescription) {
    m_description = newDescription;
}

void Event::setDay(int newDay) {
    m_date.setDay(newDay);
}

void Event::setMonth(int newMonth) {
    m_date.setMonth(newMonth);
}

void Event::setYear(int newYear) {
    m_date.setYear(newYear);
}

void Event::setTime(const std::string& newTime) {
    m_time = newTime;
}

void Event::setLink(const std::string& newLink) {
    m_link = newLink;
}


