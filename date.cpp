#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Date
{
private:
	int month, day, year;
	int days_per_month[13] = {0, 31, 28, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};
public:
	//These are constructors
	Date();
	Date(int day, int month, int year);
	//Destructor 
	~Date(){}

    bool isValid();
	bool isLeapYear();
	bool operator==(Date date2);
	bool operator<(Date date2);
	bool operator>(Date date2);
	int getDaysPerMonth();
	Date getPreviousDay();
	Date getNDaysPrevious (int days);

	void setToToday();
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	
	friend ostream& operator<<(ostream& os, const Date& dt);
};

Date::Date()
{
	//Initialize variables.
	month = 0, day = 0, year = 0;
}

Date::Date(int day, int month, int year)
{
	this->month = month;
	this->day = day;
	this->year = year;
}

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

bool Date::operator> (Date earlier){
    return earlier < *this;
}

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

Date Date::getNDaysPrevious (int days){
    Date index_date(day, month, year);

    while (days > 0){
        days--;
        index_date = index_date.getPreviousDay();
    }
    return index_date;
}

void Date::setToToday(){
    time_t today_in_seconds;
    struct tm * timeinfo;

    today_in_seconds = time(NULL);
    timeinfo = localtime(&today_in_seconds);

    day = timeinfo->tm_mday;
    month = timeinfo->tm_mon + 1;    //tm_mon is months since January
    year = timeinfo->tm_year + 1900; //tm_year years since 1900
}

int Date::getDaysPerMonth(){
    if ((month == 2) && (this->isLeapYear())){
        return 29;
    }
    else {
        return days_per_month[month];
    }
}

void Date::setDay(int d)
{
	if (d < 1 || d > 31)
		cout << "The day is invalid" << endl;
	else
	day = d;
	
}
void Date::setMonth(int m)
{
	if (m < 1 || m > 12)
		cout << "The month is invalid" << endl;
	else
	month = m;
	
}
void Date::setYear(int y)
{
	if (y < 1900 || y > 2200)
		cout << "The year is invalid" << endl;
	else
		year = y;
}

ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.day << '.' << dt.month << '.' << dt.year;
    return os;
}

int main(){

	Date date1(25,1,2021);
	Date date2;

	if (!date2.isValid()){
		date2.setToToday();
	}	

	if (date1 == date2){
		cout << "Dates " << date1 << " and " << date2 << " equal" << endl;
	} 
	else if (date1 < date2){
		cout << date1 << " is before " << date2 << endl;
	}
	else {
		cout << date1 << " is after " << date2 << endl;
	}
}