#include "Streamable.h"
namespace oop244{
	// destructor:
	Streamable::~Streamable()
	{

	}
	// Non-memenber operator overload implementation for cin and cout:
	std::ostream& operator<<(std::ostream& os, const Streamable& S)  //displays the Streamable Item
	{
		S.display(os, true);
		return os;
	}
	std::istream& operator>>(std::istream& is, Streamable& S)  //reads the Streamable Item
	{
		S.conInput(is);
		return is;
	}

}