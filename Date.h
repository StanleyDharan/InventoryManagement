// Final Project Milestone 1
// Student defined values tester
// File	ms1tester.cpp
// Version 1.0
// Date	2015/07/24
// Author	Fardad Soleimanloo
// Description
// This program test the student implementation of the Date class
// for submission.
//
// For you final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Stanley Dharan     2015/11/17           Mile stone 1
/////////////////////////////////////////////////////////////////

#ifndef _SICT_DATE_H_
#define _SICT_DATE_H_
#include <iostream>

namespace sict{
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
#define HOUR_ERROR 5
#define MIN_ERROR 6

  class Date{
  private:
    int _year;
    int _mon;
    int _day;
    int _hour;
    int _min;
    int _readErrorCode;
    bool _dateOnly;
    int value()const;
    void errCode(int errorCode);
    void set(int year, int mon, int day, int hour, int min);

  public:
    void validate();
    void set();
    int mdays()const;
    Date();
    Date(int year, int mon, int day);
    Date(int year, int mon, int day, int hour, int min = 0);
    bool operator==(const Date& D)const; 
    bool operator!=(const Date& D)const;
    bool operator<(const Date& D)const; 
    bool operator>(const Date& D)const; 
    bool operator<=(const Date& D)const;
    bool operator>=(const Date& D)const;
    int errCode()const;
    bool bad()const;
    bool dateOnly()const;
    void dateOnly(bool value);
    std::istream& read(std::istream& is = std::cin);
    std::ostream& write(std::ostream& ostr = std::cout)const;
  };
  std::ostream& operator<<(std::ostream& os, const Date& d);
  std::istream& operator>>(std::istream& is, Date& d);


}
#endif