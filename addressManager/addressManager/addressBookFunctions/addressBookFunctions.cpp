#include <iostream>
#include "address.h"
#include "menu.h"
#include "contact.h"
#include "contactOperators.hpp"

using std::cout, std::endl, std::cin, std::string, std::getline;

namespace addressBookManagement{
    //function to add in a contact
    void addContact(Address& addressBook, const Contact& newContact){
        addressBook.contacts.push_back(newContact);
    }

    //function that displays all contacts in the addressbook, if empty it will notify the user
    void displayContacts(const Address& addressBook){
        if (addressBook.contacts.empty()){
            cout << "Address book is currently empty!" << endl;
        } else{
            for(const auto& contact: addressBook.contacts){
                cout << contact;
                cout << "--------------------" << endl;
            }
        }
    }
    
    //function to search for a contact by name and print details
    void searchContact(const Address& addressBook, const string& name){
        for (const Contact& contact : addressBook.contacts){
            if(contact.fullName == name){
                cout << "Contact Found:" << endl;
                cout << "--------------------" << endl;
                cout << contact << endl;
                return;
            }
        }
        cout << "Contact with name " << name << " is not in the address book" << endl;
    }
    
    //function manages the user interface to select what they want to do in the address book program
    void manageAddressBook(Address& addressBook){
        int choice = 0;
        do{
            cout << AddContactMenu << ". Add Contact" << endl;
            cout << DisplayContactMenu << ". View Contact" << endl;
            cout << SearchContactMenu << ". Search Contact" << endl;
            cout << DeleteContactMenu << ". Delete Contact" << endl;
            cout << EditContactMenu << ". Edit Contact" << endl;
            cout << ExitMenu << ". Exit" << endl;
            
            cin >> choice;
            
            switch (choice){
                case AddContactMenu:{
                    Contact newContact;
                    cout << "Enter new contacts full name: " << endl;
                    cin.ignore();
                    getline(cin, newContact.fullName);
                    
                    cout << "Enter new contacts phone number" << endl;
                    getline(cin, newContact.phoneNumber);
                    
                    cout << "Enter new contacts email" << endl;
                    getline(cin, newContact.email);
                    
                    cout << "Enter new contacts street address" << endl;
                    getline(cin, newContact.streetAddress);
                    
                    addContact(addressBook, newContact);
                    break;
                }
                    
                case DisplayContactMenu:
                    displayContacts(addressBook);
                    break;
                    
                case SearchContactMenu:{
                    string name;
                    cout << "Enter to to search for in address book:" << endl;
                    cin.ignore();
                    getline(cin, name);
                    searchContact(addressBook, name);
                    break;
                }
                    
                case DeleteContactMenu:{
                    break;
                }
                    
                case EditContactMenu:{
                    break;
                }
                    
                case ExitMenu:
                    cout << "Thank you for using the Address Book Managament program" << endl;
                    break;
                    
                default:
                    cout << "Invalid choice." << endl;
            }
            
        }while(choice != ExitMenu);
    }

}
