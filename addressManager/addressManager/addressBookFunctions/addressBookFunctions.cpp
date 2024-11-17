#include "address.h"
#include "menu.h"
#include "contact.h"
#include "contactOperators.hpp"
#include <iostream>
#include <fstream>

using std::cout, std::endl, std::cin, std::string, std::getline, std::ifstream, std::ofstream, std::shared_ptr;

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
        for (const auto& contact : addressBook.contacts){
            if(contact.fullName == name){
                cout << "Contact Found:" << endl;
                cout << "--------------------" << endl;
                cout << contact << endl;
                return;
            }
        }
        cout << "Contact with name " << name << " is not in the address book" << endl;
    }
    
    // Function to delete contact by the name from address book
    void deleteContact(const Address& addressBook, const string& name){
        for (auto it = addressBook.contacts.begin(); it != addressBook.contacts.end(); ++it){
            if (it->fullName == name){
                addressBook.contacts.erase(it);
                cout << "Contact " << name << " has been deleted" << endl;
                return;
            }
        }
        cout << "Contact with name " << name << " not found in address book, deletion unsuccessful" << endl;
    }

    // Function to edit an existing contact
    void editContact(const Address& addressBook, const string& name){
        for(auto& contact: addressBook.contacts){
            if(contact.fullName == name){
                
            }
        }
    }

    // Function to save address book to file
    void saveToFile(const vector<shared_ptr<Contact>>& addressBook, const string& filename){
        ofstream file(filename);
        for (const auto& contact : addressBook) {
            file << contact->fullName << "," << contact->phoneNumber << "," << contact->email << "," << contact->streetAddress << endl;
        }
    }

    // Function to load address book from file
    void loadFromFile(vector<shared_ptr<Contact>>& addressBook, const string& filename) {
        ifstream file(filename);
        string line, name, phone, email, address;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            name = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find(','); phone = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find(','); email = line.substr(0, pos); line.erase(0, pos + 1);
            address = line;
            addContact(addressBook, {name, phone, email, address});
        }
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
            cout << Exit << ". Exit" << endl;
            
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
                    
                case Exit:
                    cout << "Thank you for using the Address Book Managament program" << endl;
                    break;
                    
                default:
                    cout << "Invalid choice." << endl;
            }
            
        }while(choice != Exit);
    }

}
