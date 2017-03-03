// header file includes
#define _CRT_SECURE_NO_WARNINGS
#include "Item.h"
#include <iostream>
#include <cstring>
namespace oop244{

	// constructors 
	Item::Item()
	{
		_upc[0] = '\0';
		_name = '\0';
		_price = 0;
		_taxed = true;
		_quantity = 0;
		_qtyNeeded = 0;
	}
	Item::Item(const char* upc_, const char* name_, double price_, int qtyNeeded_, bool taxed_) //copies the values to the Item class values
	{
		strncpy(_upc, upc_, MAX_UPC_LEN + 1);
		_name = new (std::nothrow) char[strlen(name_) + 1];
		strcpy(_name, name_);
		_qtyNeeded = qtyNeeded_;
		_price = price_;

	}
	Item::Item(const Item& src)  //copy constrcutor
	{
		strncpy(_upc, src._upc, MAX_UPC_LEN + 1);
		_price = src._price;
		_taxed = src._taxed;
		_quantity = src._quantity;
		_qtyNeeded = src._qtyNeeded;

		if (src._name != nullptr)
		{

			_name = new (std::nothrow) char[strlen(src._name + 1)];
			strcpy(_name, src._name);
		}
		else
			_name = nullptr;
	}


	// operator=
	Item& Item::operator=(const Item& src)   //assignment operator
	{
		strncpy(_upc, src._upc, MAX_UPC_LEN + 1);
		_price = src._price;
		_taxed = src._taxed;
		_quantity = src._quantity;
		_qtyNeeded = src._qtyNeeded;

		if (this != &src)
		{
			delete[] _name;

			if (src._name != nullptr)
			{
				_name = new (std::nothrow) char[strlen(src._name) + 1];
				strcpy(_name, src._name);
			}
			else
				_name = nullptr;
		}

		return *this;
	}



	// setters 
	void Item::upc(const char* _upc_)  //copies the passed upc to the Item upc
	{
		strcpy(_upc, _upc_);
	}

	void Item::price(const double _price_)  //copies the passed price to the Item price
	{
		_price = _price_;
	}
	void Item::name(const char* _name_)  //copies the passed name to the Item name
	{
		_name = new (std::nothrow) char[strlen(_name_) + 1];
		strcpy(_name, _name_);
	}
	void Item::taxed(const bool _taxed_)  //either true if there is tax or false otherwise
	{
		_taxed = _taxed_;
	}
	void Item::quantity(const int _quantity_)   //copies the quantity passed to the Item quantity
	{
		_quantity = _quantity_;
	}
	void Item::qtyNeeded(const int _qtyNeeded_)   //copies the quantity needed to the Item quantity needed
	{
		_qtyNeeded = _qtyNeeded_;
	}






	// getters
	const char* Item::upc() const   //returns the Item upc
	{
		return _upc;
	}
	double Item::price() const  //returns the Item price
	{
		return _price;
	}
	const char* Item::name() const  //returns the Item name
	{
		return _name;
	}
	bool Item::taxed() const  //returns the Item tax
	{
		return _taxed;
	}
	int Item::quantity() const  //returns the Item quantity
	{
		return _quantity;
	}
	int Item::qtyNeeded() const  //returns the quantity needed
	{
		return _qtyNeeded;
	}
	double Item::cost() const  //determines the cost of the price with or without tax
	{
		double cost = 0;

		if (_taxed == true)
		{
			cost = _price + _price * TAX;
		}
		else
			cost = _price;

		return cost;
	}

	// member operator overloads 
	bool Item::operator==(const char* a)  //compares the Item upc to the passed upc 
	{
		bool change;

		if (strcmp(a, _upc) == 0)
		{
			change = true;
		}
		else
		{
			change = false;
		}

		return change;
	}

	int Item::operator+=(int b)   //adds the quantity and returns it
	{
		_quantity += b;

		return _quantity;
	}

	// non-member operator overload
	double operator+=(double& d, const Item& I)  //returns the value from the cost * quantity
	{
		d += I.cost() * I.quantity();

		return d;
	}


	// destructor
	Item::~Item()   //deletes the name if it is not pointing to a nullptr
	{
		if (_name != NULL)
		{
			delete[] _name;
			_name = nullptr;
		}

	}
}