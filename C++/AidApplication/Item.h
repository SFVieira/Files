#ifndef __244_ITEM__
#define __244_ITEM__
// header file includes
#define _CRT_SECURE_NO_WARNINGS
#include "general.h"
#include "Streamable.h"
#include <iostream>
#include <cstring>
namespace oop244{

	class Item : public Streamable  {
	private:
		char _upc[MAX_UPC_LEN + 1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;
		int _qtyNeeded;


	public:
		// constructors
		Item();
		Item(const char*, const char*, double, int, bool taxed_ = true);
		Item(const Item&);

		// destructor
		~Item();

		// setters
		void upc(const char*);
		void price(const double);
		void name(const char*);
		void taxed(const bool);
		void quantity(const int);
		void qtyNeeded(const int);


		// getters
		const char* upc() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;





		// operators
		bool operator==(const char*);
		int operator+=(int);
		Item& operator=(const Item&);

	};
	// Non-member operator overload prototype
	double operator+=(double& d, const Item& I);
}


#endif