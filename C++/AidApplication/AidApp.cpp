#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"
using namespace std;
namespace oop244{

  // copy constructor and assignment operator
	AidApp::AidApp(const AidApp&)
	{

	}
	AidApp& AidApp::operator=(AidApp&)
	{
		return *this;
	}


  // constructor 
  // copies filename to _filename
  // sets all the _items to null
  // sets _noOfItems to null
  // loads the Records
  AidApp::AidApp(const char* filename){
	  
	  strcpy(_filename, filename);
	  for (int i = 0; i < MAX_NO_RECS; i++)
	  {
		  _items[i] = '\0';
	  }
	  _noOfItems = '\0';
	  loadRecs();

  }

  // Menu() displays the menu as follows and waits for the user to 
  // select an option. 
  // if the selection is valid, it will return the selection
  // if not it will return -1
  // this funtion makes sure there is no characters left in keyboard
  // and wipes it before exit.
  int AidApp::menu(){

	  int menu_;
	  int choice;

		  std::cout << "Disaster Aid Supply Management Program" << std::endl;			//the current menu
		  std::cout << "1 - List items" << std::endl;
		  std::cout << "2 - Add Non-food item Item" << std::endl;
		  std::cout << "3 - Add Perishable item" << std::endl;
		  std::cout << "4 - Update item quantity" << std::endl;
		  std::cout << "0 - exit program" << std::endl;
		  std::cout << ">";
		  std::cin >> menu_;
		  std::cout << std::endl;

		  if (menu_ >= 0 && menu_ <= 4)
		  {
			  choice = menu_;
		  }
		  else
			  choice = -1;
	  
		  
		  return choice;
  }


  // lists all the items in linear format on the screen 

  void AidApp::listItems()const{
	 
	  double totalCost = 0;

	  std::cout.setf(std::ios::left);				//prints out the lsit of items for the user to see
	  std::cout.width(4);
	  std::cout.fill(' ');
	  std::cout << " Row ";
	  std::cout << "|";
	  std::cout.width(7);
	  std::cout.fill(' ');
	  std::cout << " UPC";
	  std::cout << "|";
	  std::cout.width(20);
	  std::cout.fill(' ');
	  std::cout << " Item Name";
	  std::cout << "|";
	  std::cout.width(7);
	  std::cout.fill(' ');
	  std::cout << " Cost";
	  std::cout << "|";
	  std::cout.unsetf(std::ios::left);
	  std::cout.width(4);
	  std::cout.fill(' ');
	  std::cout << "QTY";
	  std::cout << "|";
	  std::cout.width(4);
	  std::cout.fill(' ');
	  std::cout << "Need";
	  std::cout << "|";
	  std::cout.setf(std::ios::left);
	  std::cout.width(10);
	  std::cout.fill(' ');
	  std::cout << " Unit";
	  std::cout << "|";
	  std::cout << " Expiry";
	  std::cout.unsetf(std::ios::left);
	  std::cout << std::endl;
	  std::cout.setf(std::ios::left);
	  std::cout << "-----";
	  std::cout << "|";
	  std::cout << "-------";
	  std::cout << "|";
	  std::cout << "--------------------";
	  std::cout << "|";
	  std::cout << "-------";
	  std::cout << "|";
	  std::cout << "----";
	  std::cout << "|";
	  std::cout << "----";
	  std::cout << "|";
	  std::cout << "----------";
	  std::cout << "|";
	  std::cout << "----------";
	  std::cout.unsetf(std::ios::left);
	  std::cout << std::endl;

	  for (int i = 0; i < _noOfItems; i++)				//displays the Items that were in the datafile
	  {
		  std::cout.setf(std::ios::right);
		  std::cout.width(4);
		  std::cout.fill(' ');
		  std::cout << i;
		  std::cout << " |";
		  _items[i]->display(std::cout, true);
		  std::cout << "|";
		  std::cout << std::endl;
		  std::cout.unsetf(std::ios::right);
		  totalCost = oop244::operator+=(totalCost, *_items[i]);
		  
		  
	  }

	  for (int i = 0; i < 74; i++)
	  {
		  std::cout << "-";
	  }
	  std::cout << std::endl;

	  std::cout << "Total cost of support: ";				//displays the total cost of support to the user
	  std::cout << "$";
	  std::cout.setf(std::ios::fixed);
	  std::cout.precision(2);
	  std::cout << totalCost;
	  std::cout.unsetf(std::ios::fixed);
	  std::cout << std::endl;





  }


  // opens the file for writing
  // stores the items in the file
  // closes the file
  void AidApp::saveRecs(){

	  int i;

	  datafile.open(_filename, ios::out);

	  for (i = 0; i < _noOfItems; i++)
	  {
		  _items[i]->store(datafile);					//stores the items into the file and closes the file
	  }
	  datafile.close();


  }


 // Opens the file for reading, if it does not exist, it will create an
 // empty file and exits otherwise :
 // Loads Records from the file overwriting the old ones pointed by item.
 // This function makes sure when loading records into _item pointers, they 
 // are deallocated before if they are already pointing to an item
 // closes the file

  void AidApp::loadRecs(){
	  
	  char Id;
	  int readIndex = 0;

	  datafile.open(_filename, std::ios::in);

	  if (!datafile.is_open())
	  {
		  datafile.clear();
		  datafile.close();
		  datafile.open(_filename, std::ios::out);
		  datafile.close();
	  }
	  else
	  {
		  while (datafile >> Id)
		  {
			  if (_items[readIndex] != NULL)
			  {
				  delete[] _items[MAX_NO_RECS];
			  }
			  else
			  {
				  
				  if (Id == 'P')
				  {
					  datafile.ignore(1, ',');
					  _items[readIndex] = new Perishable();
					  _items[readIndex]->load(datafile);				//loads the Perishable records into the item

				  }
				  else if (Id == 'N')
				  {
					  datafile.ignore(1, ',');
					  _items[readIndex] = new NFI();
					  _items[readIndex]->load(datafile);				//loads the Non food item records into the item
				  }
				  readIndex++;
			  }

		  } 
		  datafile.close();
		  _noOfItems = readIndex;
	  }
	  


  }

  // Searchers for the item in the _items array with the same UPC.
  // if found, it will display the item in non-linear format and then 
  // asks for the value of the items purchased, and if the value does not exceed
  // the number needed to fulfill the requirement, it will update the quantity onhand
  // value of the found record and then saves all the records to the file, overwriting 
  // the old values
  void AidApp::updateQty(const char* UPC){

	  int index = SearchItems(UPC);
	  int purchaseItem;
	  int qtyTotal;
			 


	  if (index >= 0)
	  {
		  _items[index]->display(std::cout, false);
		  std::cout << std::endl;
		  std::cout << "Please enter the number of Purchased items: ";			//asks the user for the purchase items
		  std::cin >> purchaseItem;
		  if (std::cin.fail() == true)			//the value the user put is not valid
		  {
			  std::cout << "Invalid Quantity value!";
			  std::cout << std::endl;
		  }
		  else
		  {
			  qtyTotal = _items[index]->qtyNeeded();
			  qtyTotal -= _items[index]->quantity();
			  if (purchaseItem <= qtyTotal)   //checks to see the value the user inputed is equal to or less than the current item quantity needed
			  {
				  _items[index]->operator+=(purchaseItem);
			  }
			  else if (purchaseItem > qtyTotal)		//checks to see the the value the user inputed is greater than the quantity needed
			  {

				  std::cout << "Too much items, only ";
				  std::cout << qtyTotal;
				  std::cout << " needed, please return the extra "<< purchaseItem - qtyTotal << " items.";
				  std::cout << std::endl;
				  _items[index]->operator+=(qtyTotal);

			  }
		  }
		  saveRecs();
		  std::cout << "Updated!";			//tells the user the file is updated
		  std::cout << std::endl;
		  std::cout.flush();
	  }
	  else
	  {
		  std::cout << "Not Found!";      //tells the user that the upc is not found
		  std::cout << std::endl;
		  std::cout.flush();
	  }
			  


  }


  // searches for an item in the _items array for the same upc
  // if found it will return the index of the found item in _items
  // otherwise returns -1
  int AidApp::SearchItems(const char* upc)const{

	  int index;

	  for (int i = 0; i < _noOfItems; i++)
	  {

		  if (_items[i]->operator==(upc))			//compares the upc by the user to the one in the files
		  {
			  index = i;
			  break;
		  }
		  else
		  {
			  index = -1;
		  }
	  }


	  return index;

  }


  // creates a new item (NFI or Perishable) based on the argument
  // recieved dynamically, asks the user to fill in the values
  // if the user fills the values with no mistake, it will open the file 
  // for writing, and then stores the item in the file.
  // and print a proper message. 
  // if the user makes a mistake (cin fails) it will only display the item
  // to show the error.
  // in any way it will delete the item before exiting the function
  void AidApp::addItem(bool isPerishable){

	  int writeIndex = _noOfItems;

	  if (isPerishable == true)
	  {
		  _items[writeIndex] = new Perishable();
		  _items[writeIndex]->conInput(std::cin);			//user inputs the Perishable items
		
		  if (std::cin.fail())			//checks to see if the user makes a mistake
		  {
			  std::cin.clear();
			  std::cin.ignore(2000, '\n');
			  _items[writeIndex]->display(std::cout, false);
			  std::cout << std::endl;
			  
		  }
		  else
		  {
			  _noOfItems++;
			  saveRecs();
			  std::cout << "Item added";
			  std::cout << std::endl;
		  }
		  
	  }
	  else
	  {
		  _items[writeIndex] = new NFI();
		  _items[writeIndex]->conInput(std::cin);		//user inputs the Non-food items

		  if (std::cin.fail())			//checks if the user makes a mistake
		  {
			  std::cin.clear();
			  std::cin.ignore(2000, '\n');
			  _items[writeIndex]->display(std::cout, false);
			  std::cout << std::endl;
		  }
		  else
		  {
			  _noOfItems++;
			  saveRecs();
			  std::cout << "Item added";
			  std::cout << std::endl;

		  }
	  }



  }

  // diplays the menu and receives the user selection
  // if valid, it will preform the action requsted:
  // 1, lists the items in the file on the screen
  // 2 and 3, adds the item and then re-loads the records
  //     from the file into the AidApp
  // 4, gets a UPC and then updates the quantity of it
  // 0, exits the program.
  int AidApp::run(){

	  int selection;
	  bool PorNItem;
	  char code[MAX_UPC_LEN + 1];

	  do 
	  {
		  std::cout << std::endl;
		  selection = menu();			//displays the menu
		  
		  
		  if (selection == 1)				//the different selections the user can pick
		  {
			  listItems();
		  }
		  else if (selection == 2)
		  {
			  PorNItem = false;
			  addItem(PorNItem);
		  }
		  else if (selection == 3)
		  {
			  PorNItem = true;
			  addItem(PorNItem);
		  }
		  else if (selection == 4)
		  {
			  std::cout << "Please enter the UPC: ";
			  std::cin >> code;
			  updateQty(code);
		  }
		  else if (selection == 0)
		  {
			  std::cout << "Goodbye!!";
			  std::cout << std::endl;
		  }
		  else if (selection == -1)
		  {
			  std::cout << "===Invalid Selection, try again.===";
		  }


	  } while(selection != 0);

	  return 0;
  } 
}