#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "general.h"
#include <iomanip>
#include <iostream>
using namespace std;
namespace oop244{
	// returns a unique value for a date
	// this value is used to compare two dates
	int Date::value()const{
		return _year * 372 + _mon * 31 + _day;
	}

	// validate function 


	// returns the day of the month. 
	// _mon value must be set for this to work
	// if _mon is invalid, this function returns -1
	// leap years are considered in this logic

	int Date::mdays()const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
	}

	// constructor 

	Date::Date()
	{
		_year = 0;
		_mon = 0;
		_day = 0;
		_readErrorCode = NO_ERROR;

	}
	Date::Date(int year_, int mon_, int day_, int error)		//sets the year, month, day, and errorCode#
	{
		_year = year_;
		_mon = mon_;
		_day = day_;
		_readErrorCode = error;
	}


	// member functions 
	int Date::errCode() const			//returns the current errorCode#
	{
		return _readErrorCode;
	}

	bool Date::bad() const
	{
		if (_readErrorCode != 0)
		{
			return true;
		}
		else
			return false;
	}

	void Date::errCode(int errorCode)		//receives the current errorCode and sets the Date errorCode
	{
		_readErrorCode = errorCode;
	}



	// operators
	bool Date::operator==(const Date& D) const  //compares the current objects to the Date values
	{
		if (this->value() == D.value())
		{
			return true;
		}
		else
			return false;
	}
	bool Date::operator!=(const Date& D) const
	{
		if (this->value() != D.value())
		{
			return true;
		}
		else
			return false;
	}
	bool Date::operator<(const Date& D) const
	{
		if (this->value() < D.value())
		{
			return true;
		}
		else
			return false;
	}
	bool Date::operator>(const Date& D) const
	{
		if (this->value() > D.value())
		{
			return true;
		}
		else
			return false;
	}
	bool Date::operator<=(const Date& D) const
	{
		if (this->value() <= D.value())
		{
			return true;
		}
		else
			return false;
	}
	bool Date::operator>=(const Date& D) const
	{
		if (this->value() >= D.value())
		{
			return true;
		}
		else
			return false;
	}

	// IO funtions
	std::istream& Date::read(std::istream& istr)  //the user inputs the Date
	{

		istr >> _year;
		istr.ignore(1, '/');
		istr >> _mon;
		istr.ignore(1, '/');
		istr >> _day;
	

		if (istr.fail() == true)		/*if the user enter an invalid value it will check the year, month, day and 
										sets the errorCode to the proper invalid value error*/
		{
			_readErrorCode = CIN_FAILED;
		}
		else if (_year < MIN_YEAR || _year > MAX_YEAR)
		{
			_readErrorCode = YEAR_ERROR;
		}
		else if (_mon < 1 || _mon > 12)
		{
			_readErrorCode = MON_ERROR;
		}
		else if ( _day > mdays() || _day < 1)
		{
			_readErrorCode = DAY_ERROR;
		}
		else
		{
			_readErrorCode = NO_ERROR;
		}
		

		return istr;

	}
	std::ostream& Date::write(std::ostream& ostr) const  //writes the date enter to the screen
	{
		
		ostr << _year;
		ostr << '/';
		ostr.setf(ios::right);
		ostr.fill('0');
		ostr.width(2);
		ostr << _mon;
		ostr << '/';
		ostr.fill('0');
		ostr.width(2);
		ostr << _day;
		ostr.unsetf(ios::right);

		return ostr;
	}

	// non-memeber operator overloads

	std::istream& operator>>(std::istream& is, Date& D)    //reads the Date
	{
		D.read(is);
		return is;
	}
	std::ostream& operator<<(std::ostream& os, const Date& D)  //writes the Date
	{
		D.write(os);
		return os;
	}

}