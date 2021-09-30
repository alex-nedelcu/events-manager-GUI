//
// Created by Alex Nedelcu on 21.03.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_EVENT_H
#define A89_915_NEDELCU_ALEXANDRU_EVENT_H

#include <string>
#include <iostream>
#include "Date.h"

class Event {
private:
    int m_ID;
    std::string m_title;
    std::string m_description;
    Date m_date;
    std::string m_time;
    int m_participantsNumber;
    std::string m_link;

public:
    Event();

    explicit Event(int ID);

    explicit Event(int ID, const std::string& title, const std::string& description, const Date& date, const std::string& time, int participantsNumber, const std::string& link);

    int getID() const {return m_ID;}

    const std::string& getTitle() const {return m_title;}

    const std::string& getDescription() const {return m_description;}

    const Date& getDate() const {return m_date;}

    const std::string& getTime() const {return m_time;}

    int getParticipantsNumber() const {return m_participantsNumber;}

    const std::string& getLink() const {return m_link;}

    void setTitle(const std::string& newTitle);

    void setDescription(const std::string& newDescription);

    void setDay(int newDay);

    void setMonth(int newMonth);

    void setYear(int newYear);

    void setTime(const std::string& newTime);

    void setParticipantsNumber(int newNumber) {m_participantsNumber = newNumber;}

    void setLink(const std::string& newLink);

    bool operator ==(const Event& otherEvent) const {return m_ID == otherEvent.m_ID;}

    std::string toStringComplete() const;

    std::string toStringEssentials() const;

    void prettyPrint() const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Event& event);

    /**
     * Override of >> operator
     * e.g.
     *      Event e;
     *      std::cin >> e;
     *      // from the keyboard we must introduce: 92;Title;Description;30;12;2021;21:45;15000;www.eg.com
     *      // now, in the event "e" we have the data from above
     *
     * The function basically receives an input (e.g. [92;Title;Description;30;12;2021;21:45;15000;www.eg.com]),
     * processes it and assigns to the attributes of "event" the received attributes.
     *
     * @param inputStream: the input stream object (e.g. std::cin), which contains the data read from the keyboard
     * @param event: the event in which the received data will be stored
     * @return: the input stream object, in order to allow chain reading (e.g. std::cin >> e1 >> e2 >> e3;)
     */
    friend std::istream& operator >>(std::istream& inputStream, Event& event);
};

#endif //A89_915_NEDELCU_ALEXANDRU_EVENT_H
