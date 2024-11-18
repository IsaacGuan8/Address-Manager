#ifndef addressBookFunctions_hpp
#define addressBookFunctions_hpp

#include <string>
#include <memory>
#include "contact.h"
#include "address.h"

using std::string, std::shared_ptr, std::vector;

namespace addressBookManagement{
    void addContact(Address& addressBook, const Contact& newContact);
    void displayContacts(const Address& addressBook);
    void searchContact(const Address& addressBook, const string& name);
    void deleteContact(const Address& addressBook, const string& name);
    void editContact(Contact* contactToEdit);
    void saveToFile(const Address& addressBook, const string& filename);
    void manageAddressBook(Address& addressBook);
    Contact* findContactByName(Address& addressBook, const std::string& name);
}

#endif
