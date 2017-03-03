#ifndef __244_DATE_H__
#define __244_DATE_H__
// header file includes
#include <istream>
#include <ostream>



namespace oop244{
	// Error code values go here
#define NO_ERROR 0 //no error the date is valid
#define CIN_FAILED 1 //istream failed when entering information
#define YEAR_ERROR 2 //Year value is invalid
#define MON_ERROR 3 //Month value is invalid
#define DAY_ERROR 4 //Day value is invalid

	class Date{
	private:
		// private member variables 
		int _year;
		int _mon;
		int _day;
		int _readErrorCode;

		// private memeber functions and setters
		int value()const;
		void errCode(int errorCode);

	public:
		// constructor
		Date();
		Date(int, int, int, int error = NO_ERROR);
		// operator overloads
		bool operator==(const Date& D) const;
		bool operator!=(const Date& D) const;
		bool operator<(const Date& D) const;
		bool operator>(const Date& D) const;
		bool operator<=(const Date& D) const;
		bool operator>=(const Date& D) const;



		// IO member functions
		std::istream& read(std::istream& istr);  //reads the date in YYYY/MM/DD format
		std::ostream& write(std::ostream& ostr) const;  //writes the date in YYYY/MM/DD


		// public member fucntions and getters 
		int mdays()const;  //returns the number of days in a month
		int errCode() const;  //returns the _readErrorCode 
		bool bad() const;  //Returns true if _readErrorCode != zero

	};
	// operator << and >> overloads prototypes for ostream and istream go here
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);



}
#endif