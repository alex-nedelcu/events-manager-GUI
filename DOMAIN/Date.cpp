//
// Created by Alex Nedelcu on 21.03.2021.
//

#include "Date.h"

Date::Date() : m_day{-1}, m_month{-1}, m_year{-1} {
}

Date::Date(int day, int month, int year) : m_day{day}, m_month{month}, m_year{year} {
}

bool Date::operator !=(const Date& comparisonDate) const {
    return (!(m_year == comparisonDate.m_year && m_month == comparisonDate.m_month && m_day == comparisonDate.m_day));
}

bool Date::operator ==(const Date& comparisonDate) const {
    return m_year == comparisonDate.m_year && m_month == comparisonDate.m_month && m_day == comparisonDate.m_day;
}

bool Date::operator >(const Date& comparisonDate) const {
    return m_year > comparisonDate.m_year || (m_year == comparisonDate.m_year && m_month > comparisonDate.m_month) ||
           (m_year == comparisonDate.m_year && m_month == comparisonDate.m_month && m_day > comparisonDate.m_day);
}

void Date::setDay(int newDay) {
    m_day = newDay;
}

void Date::setMonth(int newMonth) {
    m_month = newMonth;
}

void Date::setYear(int newYear) {
    m_year = newYear;
}
