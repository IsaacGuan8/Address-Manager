#ifndef helperFunctions_hpp
#define helperFunctions_hpp

// Project-specific includes
#include "address.h"

namespace helper{
    int getIntInput(const string& prompt);
    short getShortInput(const string& prompt);
    string getStringInput(const string& prompt);
    string getStateInput(const string& prompt);
    string getValidEmail(const string& prompt);
    Contact* findContactByName(Address& addressBook, const string& name);
    string removeQuotes(const string& str);
    bool compareByName(const unique_ptr<Contact>& a, const unique_ptr<Contact>& b);
}

#endif
