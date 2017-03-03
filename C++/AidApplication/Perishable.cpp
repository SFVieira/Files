// includes go here
#define _CRT_SECURE_NO_WARNINGS
#include "Perishable.h"
#include <cstring>
#include <fstream>
#include <iostream>
namespace oop244{
	// constructor
	Perishable::Perishable(const char* u, const char* n, double p, int q, bool t, const char* un)
	{
		upc(u);
		name(n);
		price(p);
		qtyNeeded(q);
		taxed(t);
		unit(un);
		
	}


	// Setters and getters 
	const Date& Perishable::expiry() const    //returns the Date expiry
	{
		return _expiry;
	}
	void Perishable::expiry(const Date &value)  //sets the value to the Date expiry
	{
		_expiry = value;
	}
	const char* Perishable::unit() const   //returns the unit 
	{
		return _unit;
	}
	void Perishable::unit(const char* value)  //sets the value to the Perishable unit
	{
		strcpy(_unit, value);
	}



	// fstream& Perishable::store(fstream& file)const
	std::fstream& Perishable::store(std::fstream& file) const  //displays the Perishable item
	{
		file << "P" << "," << upc() << "," << name() << "," << price() << "," << unit() << "," << quantity() << "," << qtyNeeded() << "," << expiry() << std::endl;
		return file;
	}




	//fstream& Perishable::load(fstream& file)
	std::fstream& Perishable::load(std::fstream& file)  //loads the Perishable item to the file
	{
		char upc_[MAX_UPC_LEN + 1];
		char _name_[30];
		double price_;
		int quantity_, qtyNeeded_;
		char unit_[11];
		Date expiry_;

		file.getline(upc_, MAX_UPC_LEN + 1, ',');
		upc(upc_);
		file.getline(_name_, 30, ',');
		name(_name_);
		file >> price_;
		price(price_);
		file.ignore(1, ',');
		file.getline(unit_, 11, ',');
		unit(unit_);
		file >> quantity_;
		quantity(quantity_);
		file.ignore(1, ',');
		file >> qtyNeeded_;
		qtyNeeded(qtyNeeded_);
		file.ignore(1, ',');
		file >> expiry_;
		expiry(expiry_);

		
		return file;
		
	}




	//ostream& Perishable::display(ostream& os, bool linear)const
	std::ostream& Perishable::display(std::ostream& ostr, bool linear) const  //displays the Perishable item in two different ways
	{
		if (_err.isClear() == false)
		{
			ostr << _err;
		}
		else
		{
			if (linear == true)
			{
				ostr.setf(std::ios::left);
				ostr.width(7);
				ostr.fill(' ');
				ostr << upc();
				ostr << "|";
				ostr.width(20);
				ostr.fill(' ');
				ostr << name();
				ostr << "|";
				ostr.unsetf(std::ios::left);
				ostr.setf(std::ios::right);
				ostr.setf(std::ios::fixed);
				ostr.precision(2);
				ostr.width(7);
				ostr.fill(' ');
				ostr << cost();
				ostr.unsetf(std::ios::fixed);
				ostr << "|";
				ostr.width(4);
				ostr.fill(' ');
				ostr << quantity();
				ostr << "|";
				ostr.width(4);
				ostr.fill(' ');
				ostr << qtyNeeded();
				ostr << "|";
				ostr.unsetf(std::ios::right);
				ostr.setf(std::ios::left);
				ostr.width(10);
				ostr.fill(' ');
				ostr << unit();
				ostr << "|";
				ostr.unsetf(std::ios::left);
				ostr << expiry();
			}
			else 
			{
				ostr << "upc: " << upc(); 
				ostr << std::endl;
				ostr << "name: " << name(); 
				ostr << std::endl;
				ostr.setf(std::ios::fixed);
				ostr.precision(2);
				ostr << "price: " << price(); 
				ostr << std::endl;
				ostr.precision(2);
				ostr << "Price after tax: " << cost();
				ostr << std::endl;
				ostr.unsetf(std::ios::fixed);
				ostr << "Quantity On hand: " << quantity(); 
				ostr << std::endl;
				ostr << "Quantity Needed: " << qtyNeeded();
				ostr << std::endl;
				ostr << "Unit: " << unit();
				ostr << std::endl;
				ostr << "Expiry date: "; 
				ostr << expiry();
				ostr << std::endl;

			}
		}

		return ostr;

	
	}



	// istream& Perishable::conInput(istream& is)
	std::istream& Perishable::conInput(std::istream& istr)  //asks the user for a Perishable entry and checks to see the values are not invalid
	{
		char upc_[MAX_UPC_LEN + 1];
		char _name_[30];
		double price_;
		int quantity_, qtyNeeded_;
		char unit_[11];
		Date expiry_;

		const char priceError[] = { "Invalid Price Entry" };
		const char quantityError[] = { "Invalid Quantity Entry" };
		const char qtyNeededError[] = { "Invalid Quantity Needed Entry" };
		const char cinFailed[] = { "Invalid Date Entry" };
		const char yearError[] = { "Invalid Year in Date Entry" };
		const char monError[] = { "Invalid Month in Date Entry" };
		const char dayError[] = { "Invalid Day in Date Entry" };

		std::cout << "Perishable Item Entry: " << std::endl;
		std::cout << "upc: ";
		istr >> upc_;
		upc(upc_);
		std::cout << "name: ";
		istr >> _name_;
		name(_name_);
		std::cout << "price: ";
		istr >> price_;
		if (istr.fail() == true)
		{
			_err.message(priceError);
		}
		else
		{
			price(price_);
			std::cout << "Quantity On hand: ";
			istr >> quantity_;
			if (istr.fail() == true)
			{
				_err.message(quantityError);
			}
			else
			{
				quantity(quantity_);
				std::cout << "Quantity Needed: ";
				istr >> qtyNeeded_;
				
				if (istr.fail() == true)
				{
					_err.message(qtyNeededError);
				}
				else
				{
					qtyNeeded(qtyNeeded_);
					std::cout << "Unit: ";
					istr >> unit_;
					unit(unit_);
					std::cout << "Expiry date (YYYY/MM/DD) : ";
					istr >> expiry_;
					if (istr.fail() == true)
					{
						_err.message(cinFailed);
						istr.setstate(std::ios::failbit);
					}
					else if (expiry_.errCode() == 2)
					{
						_err.message(yearError);
						istr.setstate(std::ios::failbit);
					}
					else if (expiry_.errCode() == 3)
					{
						_err.message(monError);
						istr.setstate(std::ios::failbit);
					}
					else if (expiry_.errCode() == 4)
					{
						_err.message(dayError);
						istr.setstate(std::ios::failbit);
					}
					else
					{
						expiry(expiry_);
						_err.clear();
					}
	
				}
			}
		}
		return istr;


	
	}
}