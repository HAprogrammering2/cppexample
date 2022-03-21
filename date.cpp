// A very simple implementation of a date class, just to highlight
// some of the features of C++.
// Compile with:  g++ -std=c++14 -c date.cpp -o date.o

#include <iostream>
#include <string>
#include <time.h>
#include "date.h"
using namespace std;

/**
 * Construct a new empty Date object
 */
Date::Date()
{
	//Initialize variables.
	month = 0, day = 0, year = 0;
}

/**
 * Construct a new Date object from values
 */
Date::Date(int day, int month, int year)
{
	this->month = month;
	this->day = day;
	this->year = year;
}

/**
 * Copy constructor: construct a new Date object from an old one
 */
Date::Date(const Date& d){
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;
}

/**
 * Checks if a date is valid
 */
bool Date::isValid (){
    if (day > 31 || 
        day < 1 ||
        month > 12 ||
        month < 1) {
            return false;
        }
    else {
        if ((month == 2) && isLeapYear()){ // February on a leap year
            return day <= 29;
        }
        else { // Not leap year, or leap year and not February
            return day <= days_per_month[month];
        }
    }
}

/**
 * Checks if date is in a leap year
 */
bool Date::isLeapYear (){
    if (year % 4 > 0){
        // Not divisible by 4, not a leap year
        return false;
    }
    else if (year % 100 == 0){
        if (year % 400 == 0){
            // Divisible by 400 --> leap year
            return true;
        }
        else {
            // Divisible by 100 but not 400 --> not leap year
            return false;
        }
    }
    else {
        // Divisible by 4 but not 100
        return true;
    }
}

/**
 * Equality operator, compares this date to another one
 * returns true if equal.
 */
bool Date::operator==(Date date2)
{
    if (day == date2.day &&
        month == date2.month &&
        year == date2.year){
        return true;
    }
    else {
        return false;
    }
}

/**
 * Less-than operator, returns true if this date is before
 * the other.
 */
bool Date::operator< (Date second){

    if(year < second.year) {
        return true;
    }
    else if (year > second.year){
        return false;
    }
    else if (month < second.month) { // year == second.year
        return true;
    }
    else if (month > second.month) {
        return false;
    }
    else if (day < second.day) {  // month == second.month
        return true;
    } 
    else { // day > second.day OR dates_equal
        return false;
    }
}

/**
 * Greater-than operator, returns true if this date
 * is after the other.
 */
bool Date::operator> (Date earlier){
    return earlier < *this;
}

/**
 * Decrease operator. Decreases this date by one day.
 */
Date& Date::operator--(){
    *this = this->getPreviousDay();
    return *this;
}

/**
 * Returns the previous day of this date. 
 */
Date Date::getPreviousDay()
{
	Date other(day, month, year);

    if (other.day == 1) {
        // Beginning of month, get previous month
        other.month = other.month - 1;

        if (other.month == 0){
            // Beginning of year, skip to December previous year
            other.year -= 1;
            other.month = 12;
        }
        // Update the day to the last day of the previous month (now in other)
        other.day = other.getDaysPerMonth();
    }
    else {
        // Not in beginning of month, just decrease day.
        other.day -= 1;
    }

    return other;
}

/**
 * Decrease operator. Decreases this date by the given 
 * number of days.
 */
Date& Date::operator-=(int n){
    *this = this->getNDaysPrevious(n);
    return *this;
}

/**
 * Decreases this date by the given number of days.
 */
Date Date::getNDaysPrevious (int days){
    Date index_date(day, month, year);

    while (days > 0){
        days--;
        index_date = index_date.getPreviousDay();
    }
    return index_date;
}

/**
 * Sets the date to today.
 */
void Date::setToToday(){
    time_t today_in_seconds;
    struct tm * timeinfo;

    today_in_seconds = time(NULL);
    timeinfo = localtime(&today_in_seconds);

    day = timeinfo->tm_mday;
    month = timeinfo->tm_mon + 1;    //tm_mon is months since January
    year = timeinfo->tm_year + 1900; //tm_year years since 1900
}

/**
 * Returns the number of days in the month of this date.
 */
int Date::getDaysPerMonth(){
    if ((month == 2) && (this->isLeapYear())){
        return 29;
    }
    else {
        return days_per_month[month];
    }
}

/**
 * Setter function for the day. Does not check that
 * the resulting date is valid.
 */
void Date::setDay(int d)
{
	if (d < 1 || d > 31)
		cout << "The day is invalid" << endl;
	else
	day = d;	
}

/**
 * Setter function for the month. Does not check that
 * the resulting date is valid.
 */
void Date::setMonth(int m)
{
	if (m < 1 || m > 12)
		cout << "The month is invalid" << endl;
	else
	month = m;	
}

/**
 * Setter function for the year. Does not check that 
 * the resulting date is valid.
 */
void Date::setYear(int y)
{
	if (y < 1900 || y > 2200)
		cout << "The year is invalid" << endl;
	else
		year = y;
}

/**
 * Outstream operator. Outputs the date in format
 * d.m.y on the given
 */
ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.day << '.' << dt.month << '.' << dt.year;
    return os;
}

/**
 * Instream operator. Inputs the date in format
 * d.m.y on the given
 */
istream& operator>>(istream& is, Date& dt)
{
    char c1, c2; // Dummy variables used to catch the delimiters. 

    is >> dt.day >> c1 >> dt.month >> c2 >> dt.year;

    if (c1 != c2 || (c1 != '.' && c1 != '/' && c1 != '-')) {
        is.setstate(std::ios::failbit);
    }

    return is;
}
