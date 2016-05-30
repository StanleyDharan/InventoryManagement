#include <iomanip>
#include <iostream>
#include <ctime>

using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict{

    void Date::set(){
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        _day = lt.tm_mday;
        _mon = lt.tm_mon + 1;
        _year = lt.tm_year + 1900;
        if (dateOnly()){
            _hour = _min = 0;
        }
        else{
            _hour = lt.tm_hour;
            _min = lt.tm_min;
        }
    }

    int Date::value()const{
        return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
    }


    int Date::mdays()const{
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
        mon--;
        return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
    }


    void Date::errCode(int errorCode){
        _readErrorCode = errorCode;
    }


    void Date::set(int year, int mon, int day, int hour, int min){
        _year = 0;
        _mon = 0;
        _day = 0;
        _hour = 0;
        _min = 0;
        _readErrorCode = NO_ERROR;
    }


    Date::Date(){
        _dateOnly = false;
        set();
    }


    Date::Date(int year, int mon, int day){
        _dateOnly = true;
        _year = year;
        _mon = mon;
        _day = day;
        _hour = 0;
        _min = 0;
        _readErrorCode = NO_ERROR;
    }


    Date::Date(int year, int mon, int day, int hour, int min){
        _dateOnly = false;
        _year = year;
        _mon = mon;
        _day = day;
        _hour = hour;
        _min = min;
        _readErrorCode = NO_ERROR;
    }


    int Date::errCode()const{
        return _readErrorCode;
    }


    bool Date::bad()const{
        if (_readErrorCode > 0){
            return true;
        }
        else return false;
    }


    bool Date::dateOnly()const{
        return _dateOnly;
    }


    void Date::dateOnly(bool value){
        _dateOnly = value;
        if (value == true){
            _hour = 0;
            _min = 0;
        }
    }


    bool Date::operator==(const Date& D)const{
        if (value() == D.value()){
            return true;
        }
        else return false;
    }
    bool Date::operator!=(const Date& D)const{
        if (value() != D.value()){
            return true;
        }
        else return false;
    }
    bool Date::operator<(const Date& D)const{
        if (value() < D.value()){
            return true;
        }
        else return false;
    }
    bool Date::operator>(const Date& D)const{
        if (value() > D.value()){
            return true;
        }
        else return false;
    }
    bool Date::operator<=(const Date& D)const{
        if (value() <= D.value()){
            return true;
        }
        else return false;
    }
    bool Date::operator>=(const Date& D)const{
        if (value() >= D.value()){
            return true;
        }
        else return false;
    }


    void Date::validate(){
        _readErrorCode = NO_ERROR;
        if (_year > MAX_YEAR || _year < MIN_YEAR){
            _readErrorCode = YEAR_ERROR;
        }
        else if (_mon > 12 || _mon < 1){
            _readErrorCode = MON_ERROR;
        }
        else if (_day > mdays() || _day < 1){
            _readErrorCode = DAY_ERROR;
        }
        if (_dateOnly == false){
            if (_hour > 24 || _hour < 1){
                _readErrorCode = HOUR_ERROR;
            }
            else if (_min > 59){
                _readErrorCode = MIN_ERROR;
            }
        }
    }


    std::istream& Date::read(std::istream& is){
            is >> _year;
            is.ignore(1);
            is >> _mon;
            is.ignore(1);
            is >> _day;
       
        if (_dateOnly == false){
            is.ignore(2);
            is >> _hour;
            is.ignore(1);
            is >> _min;
        }
        if (is.fail() == true){
            _readErrorCode = CIN_FAILED;
        }
        else validate();
        return is;
    }


    std::ostream& Date::write(std::ostream& ostr)const{
        ostr << _year << "/" << _mon << "/" << setw(2) << setfill('0') << _day;
        if (_dateOnly == false){
            ostr << "," << _hour << ":" << _min;
        }
        return ostr;
    }


    std::ostream& operator<<(std::ostream& os, const Date& d){
        return d.write(os);
    }
    
    
    std::istream& operator>>(std::istream& is, Date& d){
        d.read(is);
        return is;
    }
};
