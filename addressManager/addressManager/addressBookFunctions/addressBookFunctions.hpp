#ifndef addressBookFunctions_hpp
#define addressBookFunctions_hpp

#include <string>
#include "address.h"

using std::string;

namespace addressBookManagement{
    void addContact(const Address& addressBook);
    void displayContacts(const Address& addressBook);
    void searchContact(const Address& addressBook, const string& name);
    void deleteContact();
    void manageAddressBook(Address& addressBook);
}

#endif
