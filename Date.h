/* Md Nuhel Nawaz Chowdhury
ID: 109455162
Sec: AB
Milestone 1 */

#pragma once
#include <iostream>
#ifndef MILESTONE_DATE_H
#define MILESTONE_DATE_H

namespace sict
{
	const int min_year = 2000;
	const int max_year = 2030;
	const int NO_ERROR = 0; //  --No error - the date is valid
	const int CIN_FAILED = 1;//  --istream failed on information entry
	const int YEAR_ERROR = 2; //  --Year value is invalid
	const int MON_ERROR = 3; // --Month value is invalid
	const int DAY_ERROR = 4; // --Day value is invalid


	class Date
	{
	private:
		int myear;
		int mmonth;
		int mday;
		int error;
		int value;
		int comparatorvalue()const;
		int mdays(int mon, int year) const; //Retruns the number of valid days in months and years.
		void errCode(int errorCode); /*This function sets the
									 error state variable to one of the values
									 listed above.*/

	public:
		
		Date(); // Default constructor.
		
		bool isEmpty()const;

		Date(int year, int month, int day);/*accepts in its parameters integer
										   values for the year, month and day.
										   This constructorchecks if each number is in range, in the order of year,
										   month and day.
										   If any of the numbers are not
										   within range, this function sets the error state to the
										   appropriate error code and stops further validation. */
		bool operator==(const Date&rhs)const;
		bool operator!=(const Date&rhs)const;
		bool operator<(const Date&rhs)const;
		bool operator>(const Date&rhs)const;
		bool operator<=(const Date&rhs)const;
		bool operator>=(const Date&rhs)const;
		int errCode()const; //This query returns the error state as an error code value.
		bool bad()const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;


		
	};
	//Helper functions:
	std::ostream& operator <<(std::ostream& ostr, Date& day);
	std::istream& operator >>(std::istream& istr, Date& day);

}

#endif
