#ifndef addressBookFunctions_hpp
#define addressBookFunctions_hpp

#include <string>
#include <memory>
#include "contact.h"
#include "address.h"

using std::string, std::shared_ptr, std::vector;

namespace addressBookManagement{
    void addContact(const Address& addressBook);
    void displayContacts(const Address& addressBook);
    void searchContact(const Address& addressBook, const string& name);
    void deleteContact(const Address& addressBook, const string& name);
    void editContact(const Address& addressBook, const string& name);
    void saveToFile(const vector<shared_ptr<Contact>>& addressBook, const string& filename);
    void loadFromFile()
    void manageAddressBook(Address& addressBook);
}

#endif
