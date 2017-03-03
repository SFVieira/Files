#ifndef __244_NFI_H__
#define __244_NFI_H__

// includes go here
#define _CRT_SECURE_NO_WARNINGS_
#include "ErrorMessage.h"
#include "Item.h"
#include <string.h>
#include <iostream>
#include <fstream>

namespace oop244{
  class NFI : public Item{
  private:
    ErrorMessage _err;
  public:
    // default constructor
	  NFI(const char* u = "", const char* n = "", double p = 0, int q = 1);
    // pure virutal method implementation prototypes
	  std::fstream& store(std::fstream&) const;
	  std::fstream& load(std::fstream&);
	  std::ostream& display(std::ostream&, bool) const;
	  std::istream& conInput(std::istream&);

  };
}
#endif