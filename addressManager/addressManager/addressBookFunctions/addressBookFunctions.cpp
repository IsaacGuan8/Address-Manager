#include <iostream>
#include "address.h"
#include "menu.h"
#include "contact.h"
#include "contactOperators.hpp"

using std::cout, std::endl, std::cin, std::string, std::getline;

namespace addressBookManagement{
    void addContact(Address& addressBook, const Contact& newContact){
        addressBook.contacts.push_back(newContact);
    }

    void displayContacts(const Address& addressBook){
        if (addressBook.contacts.empty()){
            cout << "Adress book is currently empty!" << endl;
        } else{
            for(const auto& contact: addressBook.contacts){
                cout << contact;
                cout << "--------------------" << endl;
            }
        }
    }

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
                    
                case DeleteContactMenu:{
                    break;
                }
                    
                case EditContactMenu:{
                    break;
                }
                    
                case ExitMenu:
                    break;
                    
                default:
                    cout << "Invalid choice." << endl;
            }
            
        }while(choice != ExitMenu);
    }

}
