#ifndef helperFunctions_hpp
#define helperFunctions_hpp

// Project-specific includes
#include "address.h"
#include "menu.h"
#include "editContactMenu.h"

namespace helper{
    int getIntInput(const string& prompt);
    short getShortInput(const string& prompt);
    string getStringInput(const string& prompt);
    string getStateInput(const string& prompt);
    string getValidEmail(const string& prompt);
    Contact* findContactByName(Address& addressBook, const string& name);
    string removeQuotes(const string& str);
    bool compareByName(const unique_ptr<Contact>& a, const unique_ptr<Contact>& b);
    int toInt(MenuChoice choice);
    int toInt(EditContactMenu choice);
    void displayMenu();
    void displayEditMenu(Contact* contactToEdit);
}

#endif
