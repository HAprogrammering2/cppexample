#include <iostream>
#ifndef DATE_H
#define DATE_H

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
    Date(const Date& d);

	//Destructor 
	~Date(){}

    // Methods for getting data
    bool isValid();
	bool isLeapYear();
	int getDaysPerMonth();
	Date getPreviousDay();
	Date getNDaysPrevious (int days);

    // Methods for setting data
	void setToToday();
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	
    // These are overloaded operators
	bool operator==(Date date2);
	bool operator<(Date date2);
	bool operator>(Date date2);
    Date& operator--();
    Date& operator-=(int n);

    // Overloading operators of the input and output streams' classes
	friend ostream& operator<<(ostream& os, const Date& dt);	
    friend istream& operator>>(istream& os, Date& dt);

};

#endif