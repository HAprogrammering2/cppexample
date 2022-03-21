// A very simple test of the date class
// Compile with:  g++ -std=c++14 date.cpp datetest.cpp
#include <iostream>
#include "date.h"

using namespace std;

int main(){

	Date date1(25,1,2021);  // Constructor with params
	Date date2;             // Default constructor

	if (!date2.isValid()){
		date2.setToToday();
	}	

	Date date3(date2);      // Copy constructor
    date1 = date2;          // Default memberwise assignment
    --date1;
    date1 -= 20;

	cout << "Please enter a date (d.m.y): ";
	cin >> date3;

	if (!cin.fail() && date3.isValid()) {

		if (date1 == date3){
			cout << "Dates " << date1 << " and " << date3 << " equal" << endl;
		} 
		else if (date1 < date3){
			cout << date1 << " is before " << date3 << endl;
		}
		else {
			cout << date1 << " is after " << date3 << endl;
		}
	}
	else {
		cout << "Invalid input" << endl;
	}


}