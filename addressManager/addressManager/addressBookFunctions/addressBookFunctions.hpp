#ifndef addressBookFunctions_hpp
#define addressBookFunctions_hpp

#include <string>
#include "address.h"

using std::string;

namespace addressBookManagement{
    void manageAddressBook(Address& addressBook);
    void addContact();
    void displayContacts();
    void deleteContact();
}

#endif
