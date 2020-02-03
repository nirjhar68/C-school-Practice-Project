#include <iostream>
#include "Date.h"
#include <iomanip>
namespace sict
{
	// Given codes. Returns the valid days.
	int Date::mdays(int mon, int year)const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	Date::Date() 
	{

		this->myear = 0;
		this->mmonth = 0;
		this->mday = 0;
		this->value = 0;
	

		errCode(NO_ERROR);

	}

	Date::Date(int y, int m, int d) {



		if (m < 13 && m >0)

		{
			mmonth = m;
			if (y > 0)
			{
				myear = y;
				if (d > 0 && d <= mdays(m, y))

				{
					mday = d;
				}
				else {

					errCode(DAY_ERROR);
					myear = 0;
					mmonth = 0;
					mday = 0;
				}

				if ((y > 0) && (m < 32 && m>0) && (d > 0 && d < 32))
				{
					value = myear * 372 + mmonth * 13 + mday;

				}
			}
			else
			{
				errCode(YEAR_ERROR);
				myear = 0;
				mmonth = 0;
				mday = 0;

			}

		}
		else
		{
			errCode(MON_ERROR);
			myear = 0;
			mmonth = 0;
			mday = 0;
		}



	}



	int Date::comparatorvalue()const {
		return myear * 372 + mmonth * 31 + mday;
	}

	bool Date::operator==(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() == rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool Date::operator!=(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() != rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	bool Date::operator<(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() < rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool Date::operator>(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() > rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	bool Date::operator<=(const Date& rhs) const
	{

		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() <= rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}

		}
		return false;

	}

	bool Date::operator>=(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty())
		{
			if (comparatorvalue() >= rhs.comparatorvalue())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;

	}

	int Date::errCode()const
	{

		return error;

	}

	bool Date::bad()const
	{


		if (error != NO_ERROR)

			return true;
		else
			return false;

	}

	std::istream & Date::read(std::istream & istr)
	{
		char dataA;
		istr.clear();
		errCode(NO_ERROR);
		istr >> myear >> dataA >> mmonth >> dataA >> mday;
		if (istr.fail()) {
			myear = 0;
			mmonth = 0;
			mday = 0;

			errCode(CIN_FAILED);
		}
		else if (min_year > myear || myear > max_year) {
			myear = 0;
			mmonth = 0;
			mday = 0;

			errCode(YEAR_ERROR);
		}
		else if (1 > mmonth || mmonth > 12) {
			myear = 0;
			mmonth = 0;
			mday = 0;

			errCode(MON_ERROR);
		}
		else if (mday> mdays(mmonth, myear)) {
			myear = 0;
			mmonth = 0;
			mday = 0;

			errCode(DAY_ERROR);
		}

		istr.clear();

		return istr;
	}

	std::ostream & sict::Date::write(std::ostream & ostr) const
	{

		ostr <<myear << '/' << std::setw(2) << std::setfill('0') << mmonth << '/' << std::setw(2) << std::setfill('0') << mday;

		return ostr;
	}


	void Date::errCode(int errorCode) {


		error = errorCode;

	}


	bool Date::isEmpty()const {

		if (myear == 0 && mmonth == 0 && mday == 0) {

			return true;
		}
		else {

			return false;
		}


	}



	std::istream & operator>>(std::istream &ist, Date & s)
	{
		return s.read(ist);
	}

	std::ostream & operator<<(std::ostream &ost, const Date & k)
	{
		return k.write(ost);
	}

}
