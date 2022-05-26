#ifndef DATE_INTERFACE_H
#define DATE_INTERFACE_H

#include "Exception.h"

class DateInterface {
protected:
    const static int FEBRUARY               = 1;
    const static int LEAP_FEBRUARY          = 2;
    const static int AUGUST                 = 3;
    const static int MORE_EXTENSIVE_MONTHS  = 4;
    const static int LESS_EXTENSIVE_MONTHS  = 5;
    const static char dayFormat             = 'd';
    const static char monthFormat           = 'm';
    const static char yearFormat            = 'a';
    string format;
    int day;
    int month;
    int year;
    char separator;
    bool isTheCurrentYearLeap() {
        if((year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0) {
            return true;
        } else {
            return false;
        }
    };
    int getTheCurrentMonth() {
        if(month % 2 == 0) {
            if(month == 2) {
                if(isTheCurrentYearLeap()) {
                    return LEAP_FEBRUARY;
                } else {
                    return FEBRUARY;
                }
            } else if(month == 8) {
                return AUGUST;
            } else {
                return LESS_EXTENSIVE_MONTHS;
            }
        } else {
            return MORE_EXTENSIVE_MONTHS;
        }
    };
    void checkDate() {
        if(getTheCurrentMonth() == LEAP_FEBRUARY) {
            if(day > 29) {
                throw Exception::invalidDate();
            }
        } else if(getTheCurrentMonth() == FEBRUARY) {
            if(day > 28) {
                throw Exception::invalidDate();
            }
        } else if(getTheCurrentMonth() == AUGUST) {
            if(day > 31) {
                throw Exception::invalidDate();
            }
        } else if(getTheCurrentMonth() == LESS_EXTENSIVE_MONTHS) {
            if(day > 30) {
                throw Exception::invalidDate();
            }
        } else if(getTheCurrentMonth() == MORE_EXTENSIVE_MONTHS) {
            if(day > 31) {
                throw Exception::invalidDate();
            }
        } else {
            throw Exception::invalidDate();
        }
        if(isTheCurrentYearLeap() && (month == 2 && day == 29)) {
            throw Exception::leapYear();
        }
        if(year < 0 || month < 0 || day < 0) {
            throw Exception::invalidDate();
        }
        if(year > 9999) {
            throw Exception::invalidYear();
        }
        if(month > 12) {
            throw Exception::invalidMonth();
        }
        if(day > 31) {
            throw Exception::invalidDay();
        }
    };
private:
    void formatDateToParams(string _date, int postions[8]) {
        string tempDay, tempMonth, tempYear;
        tempYear.push_back(_date[postions[0]]);
        tempYear.push_back(_date[postions[1]]);
        tempYear.push_back(_date[postions[2]]);
        tempYear.push_back(_date[postions[3]]);
        tempMonth.push_back(_date[postions[4]]);
        tempMonth.push_back(_date[postions[5]]);
        tempDay.push_back(_date[postions[6]]);
        tempDay.push_back(_date[postions[7]]);
        year    = stod(tempYear);
        month   = stod(tempMonth);
        day     = stod(tempDay);
        checkDate();
    };
public:
    DateInterface(string _format, string _date) {
        format = _format;
        if(_format[0] == yearFormat) {
            int positions[8]    = {0,1,2,3,5,6,8,9};
            separator           = _date[4];
            formatDateToParams(_date, positions);
        } else if(_format[0] == dayFormat) {
            int positions[8]    = {6,7,8,9,3,4,0,1};
            separator           = _date[2];
            formatDateToParams(_date, positions);
        } else if(_format[0] == monthFormat) {
            int positions[8]    = {6,7,8,9,0,1,3,4};
            separator           = _date[2];
            formatDateToParams(_date, positions);
        } else {
            throw Exception::undefinedDateFormat();
        }
    };

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }
    
    virtual string getDate()                                = 0;
    virtual string getDateWithTheNewFormat(string format)   = 0;
    virtual string getDateInFull()                          = 0;
    virtual string sumYear(int days)                        = 0;
    virtual string subtractYear(int days)                   = 0;
    virtual string sumMonth(int months)                     = 0;
    virtual string subtractMonth(int months)                = 0;
    virtual string sumDay(int days)                         = 0;
    virtual string subtractDay(int days)                    = 0;
    ~DateInterface() {};
};

#endif