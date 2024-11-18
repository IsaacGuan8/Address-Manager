#include "address.h"
#include "menu.h"
#include "contact.h"
#include "contactOperators.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>


using std::cout, std::endl, std::cin, std::string, std::getline, std::ifstream, std::ofstream, std::remove_if;

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
    void deleteContact(Address& addressBook, const string& name) {
        // Use remove_if to find the contact by name and remove it from the vector
        auto it = remove_if(addressBook.contacts.begin(), addressBook.contacts.end(), [&name](const Contact& contact) { return contact.fullName == name;});

        // If the contact is found, erase it from the vector
        if (it != addressBook.contacts.end()) {
            addressBook.contacts.erase(it, addressBook.contacts.end());
            cout << "Contact deleted." << std::endl;
        } else {
            cout << "Contact not found." << std::endl;
        }
    }

    // Function to edit an existing contact
    void editContact(Contact* contactToEdit){
        // If contact not found
        if (contactToEdit == nullptr){
                std::cout << "Invalid contact. Cannot edit." << std::endl;
                return;
            }
        
        int choice = 0;
        do {
            cout << "\nEditing Contact: " << contactToEdit->fullName << std::endl;
            cout << "1. Edit Full Name" << std::endl;
            cout << "2. Edit Phone Number" << std::endl;
            cout << "3. Edit Email" << std::endl;
            cout << "4. Edit Street Address" << std::endl;
            cout << "5. Exit Edit Menu" << std::endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice) {
                case 1:
                    cout << "Enter new full name: ";
                    getline(std::cin, contactToEdit->fullName);
                    break;
                case 2:
                    cout << "Enter new phone number: ";
                    getline(std::cin, contactToEdit->phoneNumber);
                    break;
                case 3:
                    cout << "Enter new email: ";
                    getline(std::cin, contactToEdit->email);
                    break;
                case 4:
                    cout << "Enter new street address: ";
                    getline(std::cin, contactToEdit->streetAddress);
                    break;
                case 5:
                    cout << "Exiting edit menu." << std::endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 5);
    }
    // Helper function to find contact for editContact
    Contact* findContactByName(Address& addressBook, const std::string& name) {
        for (auto& contact : addressBook.contacts) {
            if (contact.fullName == name) {
                return &contact;
            }
        }
        return nullptr; // Return nullptr if contact is not found
    }

    // Function to save address book to file
    void saveToFile(const Address& addressBook, const string& filename) {
            ofstream outFile(filename);  // Open the file for writing

            if (!outFile.is_open()){  // Check if the file was opened successfully
                cout << "Error opening " << filename << " for writing." << endl;
                return;
            }
        
            // Write CSV header
            outFile << "Full Name,Phone Number,Email, Street Address\n";

            // Loop through each contact and write their details in CSV format
            for (const auto& contact : addressBook.contacts) {
                outFile << '"' << contact.fullName << "\","
                        << '"' << contact.phoneNumber << "\","
                        << '"' << contact.email << "\","
                        << '"' << contact.streetAddress << "\",";
            }

            outFile.close();  // Close the file
            cout << "Contacts have been saved to " << filename << endl;
    }

    // Function to load address book from file
    void loadFromFile(const Address& addressBook, const string& filename){
        ifstream file(filename);
        
        
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
                    string name;
                    cout << "Enter the name of the contact to delete: " << endl;
                    cin.ignore();
                    getline(cin, name);
                    deleteContact(addressBook, name);
                    break;
                }
                    
                case EditContactMenu:{
                    // Edit contact by name
                    string name;
                    cout << "Enter the name of the contact to edit: " << endl;
                    cin.ignore();
                    getline(cin, name);

                    // Use the new helper function to find the contact
                    Contact* contactToEdit = findContactByName(addressBook, name);
                    
                    if (contactToEdit != nullptr){
                        editContact(contactToEdit);
                    } else {
                        cout << "Contact not found." << endl;
                    }
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
