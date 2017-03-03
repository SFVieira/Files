//includes go here
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <cstring>
#include "NFI.h"
namespace oop244{
  // constructor
	NFI::NFI(const char* u, const char* n,double p, int q)
	{
		upc(u);
		name(n);
		price(p);
		qtyNeeded(q);
	}

    
  // fstream& NFI::store(fstream& file)const
	std::fstream& NFI::store(std::fstream& file) const  //displays the Non-food entry to the file
	{
		file << "N" << "," << upc() << "," << name() << "," << price() << "," << quantity() << "," << qtyNeeded() << std::endl;

		return file;
	}


  // fstream& NFI::load(fstream& file)
	std::fstream& NFI::load(std::fstream& file) //loads the Non-food entry item
	{
		char _upc_[MAX_UPC_LEN + 1];
		char _name_[30];
		double _price_;
		int _quantity_, _qtyNeeded_;

		file.getline(_upc_, MAX_UPC_LEN + 1, ',');
		upc(_upc_);
		file.getline(_name_, 30, ',');
		name(_name_);
		file >> _price_;
		price(_price_);
		file.ignore(1, ',');
		file >> _quantity_;
		quantity(_quantity_);
		file.ignore(1, ',');
		file >> _qtyNeeded_;
		qtyNeeded(_qtyNeeded_);

		return file;
	}
    
    
  // ostream& NFI::display(ostream& ostr, bool linear)const
	std::ostream& NFI::display(std::ostream& ostr, bool linear) const  //displays the Non-food entry item in two different ways
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
				ostr.unsetf(std::ios::right);
		
			}
			else
			{
				ostr << "Upc: " << upc();
				ostr << std::endl;
				ostr << "Name: " << name();
				ostr << std::endl;
				ostr.setf(std::ios::fixed);
				ostr.precision(2);
				ostr << "Price: " << price();
				ostr << std::endl;
				ostr.precision(2);
				ostr << "Price after tax: " << cost();
				ostr.unsetf(std::ios::fixed);
				ostr << std::endl;
				ostr << "Quantity On Hand: " << quantity();
				ostr << std::endl;
				ostr << "Quantity Needed: " << qtyNeeded();

				ostr << std::endl;
			}
		}
		return ostr;
	}


  // istream& NFI::conInput(istream& istr)
	std::istream& NFI::conInput(std::istream& istr)  //asks the user to enter the Non-food entry and checks the values
	{
		char upc_[MAX_UPC_LEN + 1];
		char n[30];
		double price_;
		int quantity_, qtyNeeded_;
		const char priceError[] = { "Invalid Price Entry" };
		const char quantityError[] = { "Invalid Quantity Entry" };
		const char qtyNeededError[] = { "Invalid Quantity Needed Entry" };

		std::cout << "Non-Food Item Entry:" << std::endl;
		std::cout << "Upc: ";
		istr >> upc_;
		upc(upc_);
		std::cout << "Name: ";
		istr >> n;
		name(n);
		std::cout << "Price: ";
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
					_err.clear();
				}
				
			}
		}
		return istr;

	}

}