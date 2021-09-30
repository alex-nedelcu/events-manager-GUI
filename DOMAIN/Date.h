//
// Created by Alex Nedelcu on 21.03.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_DATE_H
#define A89_915_NEDELCU_ALEXANDRU_DATE_H

class Date {
private:
    int m_day;
    int m_month;
    int m_year;

public:
    Date();

    explicit Date(int day, int month, int year);

    int getDay() const {return m_day;}

    int getMonth() const {return m_month;}

    int getYear() const {return m_year;}

    void setDay(int newDay);

    void setMonth(int newMonth);

    void setYear(int newYear);

    bool operator ==(const Date& comparisonDate) const;

    bool operator !=(const Date& comparisonDate) const;

    bool operator >(const Date& comparisonDate) const;
};

#endif //A89_915_NEDELCU_ALEXANDRU_DATE_H
