#ifndef addressBookFunctions_hpp
#define addressBookFunctions_hpp

// Standard C++ libraries
#include <string>
#include <memory>

// Project-specific includes
#include "contact.h"
#include "address.h"

using std::string, std::shared_ptr, std::vector;

namespace addressBookManagement{
    void addContact(Address& addressBook, const Contact& newContact);
    void displayContacts(const Address& addressBook);
    void searchContact(const Address& addressBook, const string& name);
    void deleteContact(const Address& addressBook, const string& name);
    void editContact(Contact* contactToEdit);
    void saveToFile(const Address& addressBook, const string& filepath);
    void loadFromFile(Address& addressBook, const string& filepath);
    void sortContactsByName(vector<std::unique_ptr<Contact>>& contacts);
    void manageAddressBook(Address& addressBook);
}

#endif
