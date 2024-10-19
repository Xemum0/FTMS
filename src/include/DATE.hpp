//
//  DATE.hpp
//  FTMS_PROJECT
//
//  Created by youcef mhammdi on 01/12/2023.
//

#ifndef DATE_hpp
#define DATE_hpp
#include <iostream>
using std::cout;
using std::endl;


class Date
{
public:
    // Interface

    // Constructor
    Date(int year = 1900, int month = 1, int day = 1);

    // Copy constructor
    Date(const Date& d);

    // Destructor
    ~Date();

    // Getter methods
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    // Setter methods
    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);

    // Operator overloads
    Date& operator=(const Date& d);
    Date& operator+=(int day);
    Date operator+(int day);
    Date& operator-=(int day);
    Date operator-(int day);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    bool operator>(const Date& d);
    bool operator==(const Date& d) const;
    /* friend bool operator==(const Date& d1, const Date& d2); */
    bool operator>=(const Date& d);
    bool operator<(const Date& d);
    bool operator<=(const Date& d);
    bool operator!=(const Date& d);
    int operator-(const Date& d);
    void Print() const;


private:
    int _year;
    int _month;
    int _day;
    int GetMonthDay(int year, int month)const{
        static int monthDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int days = monthDays[month];
        if ((month == 2 && (year % 4 == 0 && year % 100 != 0)) || year % 400 == 0)
        {
            if (month==2) return 29 ;
            else return days;
        }
        return days;
    };
};
std::string dateToString(Date d);
Date stringToDate(std::string str);
int dateToSeason(Date & d);

#endif


