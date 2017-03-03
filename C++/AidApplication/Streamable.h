#ifndef __244__Streamable__
#define __244__Streamable__
// hearfile includes:
#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include <fstream>
namespace oop244{
	class Streamable{
	public:
		// pure virutal methods:
		virtual std::fstream& store(std::fstream&) const = 0;
		virtual std::fstream& load(std::fstream&) = 0;
		virtual std::ostream& display(std::ostream&, bool) const = 0;
		virtual std::istream& conInput(std::istream&) = 0;

		// virutal destructor:
		virtual ~Streamable();
	};
	// Non-memenber operator overload prototypes for cin and cout:
	std::istream& operator>>(std::istream&, Streamable&);
	std::ostream& operator<<(std::ostream&, const Streamable&);



}
#endif