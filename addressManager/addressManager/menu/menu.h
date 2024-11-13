#ifndef menu_h
#define menu_h

// Enum to represent the different menu choices in the Address Book Program
enum Menu{
    AddContactMenu = 1, // Option to add contact
    DisplayContactMenu, // Option to view all contacts stored in the address book
    SearchContactMenu,  // Option to search for a specific contact by name
    DeleteContactMenu,  // Option to delete a contact by name from the address book
    EditContactMenu,    // Option to exit the program
    ExitMenu
};
#endif
