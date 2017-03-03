#ifndef __244_AIDAPP_H__
#define __244_AIDAPP_H__
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "Perishable.h"
#include "NFI.h"
#include <fstream>
namespace oop244{
  class AidApp{
    // private member arguments
	  char _filename[256];
	  Item* _items[MAX_NO_RECS];
	  std::fstream datafile;
	  int _noOfItems;


    // copy constructor and assingment operator
    // to prevent copying and assignment
	  AidApp(const AidApp&);
	  AidApp& operator=(AidApp&);


    // private member fucntions
	  int menu();
	  void loadRecs();
	  void saveRecs();
	  void listItems()const;
	  int SearchItems(const char*) const;
	  void updateQty(const char*);
	  void addItem(bool isPerishable);

  public:
    // constructor and run member function
	  AidApp(const char*);
	  int run();

  };
}
#endif
