#include "address.h"
#include "menu.h"
#include "contact.h"
#include "editContactMenu.h"
#include "contactOperators.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>


using std::cout, std::endl, std::cin, std::string, std::getline, std::ifstream, std::ofstream, std::remove_if, std::stringstream;

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
                cout << "Invalid contact. Cannot edit." << endl;
                return;
            }
        
        int editChoice = 0;
        do {
            // Display menu for edit choices
            cout << "Editing Contact: " << contactToEdit->fullName << endl;
            cout << EditFullName << ". Edit Full Name" << endl;
            cout << EditPhoneNumber << ". Edit Phone Number" << endl;
            cout << EditEmail << ". Edit Email" << endl;
            cout << EditStreetNumber << ". Edit Street Number" << endl;
            cout << EditStreetName << ". Edit Street Name" << endl;
            cout << EditCity << ". Edit City" << endl;
            cout << EditState << ". Edit State" << endl;
            cout << EditAreaCode << ". Edit Area Code" << endl;
            cout << ExitAndSave << ". Save and Exit Edit Menu" << endl;
            
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore(); // Clear input buffer

            switch (editChoice) {
                case EditFullName:
                    cout << "Enter new full name: ";
                    getline(cin, contactToEdit->fullName);
                    break;
                    
                case EditPhoneNumber:
                    cout << "Enter new phone number: ";
                    getline(cin, contactToEdit->phoneNumber);
                    break;
                    
                case EditEmail:
                    cout << "Enter new email: ";
                    getline(cin, contactToEdit->email);
                    break;
                    
                case EditStreetNumber:
                    cout << "Enter new street number: ";
                    cin >> contactToEdit->address.streetNumber;
                    break;
                    
                case EditStreetName:
                    cout << "Enter new street name: ";
                    cin >> contactToEdit->address.streetName;
                    break;
                    
                case EditCity:
                    cout << "Enter new city: ";
                    cin >> contactToEdit->address.city;
                    break;
                    
                case EditState:
                    cout << "Enter new state: ";
                    cin >> contactToEdit->address.state;
                    break;
                    
                case EditAreaCode:
                    cout << "Enter new area code: ";
                    cin >> contactToEdit->address.areaCode;
                    break;
                    
                case ExitAndSave:
                    cout << "Exiting edit menu." << endl;
                    break;
                    
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }while(editChoice != ExitAndSave);
    }

    // Helper function to find contact for editContact
    Contact* findContactByName(Address& addressBook, const string& name){
        for (auto& contact : addressBook.contacts){
            if (contact.fullName == name){
                return &contact;
            }
        }
        return nullptr; // Return nullptr if contact is not found
    }

    // Function to save address book to file
    void saveToFile(const Address& addressBook, const string& filename){
            ofstream outFile(filename);  // Open the file for writing

            if (!outFile.is_open()){  // Check if the file was opened successfully
                cout << "Error opening " << filename << " for writing." << endl;
                return;
            }
        
            // Write CSV header
            outFile << "Full Name,Phone Number,Email, Street Address\n";

            // Loop through each contact and write their details in CSV format
            for (const auto& contact : addressBook.contacts){
                outFile << '"' << contact.fullName << "\","
                        << '"' << contact.phoneNumber << "\","
                        << '"' << contact.email << "\","
                        << '"' << contact.address.streetNumber << "\","
                        << '"' << contact.address.streetName << "\","
                        << '"' << contact.address.city << "\","
                        << '"' << contact.address.state << "\","
                        << '"' << contact.address.areaCode << "\",";
            }

            outFile.close();  // Close the file
            cout << "Contacts have been saved to " << filename << endl;
    }

    // Function to load address book from file
    void loadFromFile(Address& addressBook, const string& filename){
        ifstream inFile(filename);
        
        if (!inFile.is_open()){  // Check if the file was opened successfully
            cout << "Error opening " << filename << " for writing." << endl;
            return;
        }
        
        string line;
        bool isFirstLine = true; // to skip the CSV header
        
        while(getline(inFile, line)){
            if(isFirstLine){
                isFirstLine = false;
                continue;
            }
            
            // use of string stream to parse CSV line
            stringstream ss(line);
            Contact contact;
            
            // Read each field that is sperated by a comma
            getline(ss, contact.fullName, ',');
            getline(ss, contact.phoneNumber, ',');
            getline(ss, contact.email, ',');
            
            // Read the nested address fields
            string streetNumberStr;
            string areaCodeStr;
            getline(ss, streetNumberStr, ',');
            getline(ss, contact.address.streetName, ',');
            getline(ss, contact.address.city, ',');
            getline(ss, contact.address.state, ',');
            getline(ss, areaCodeStr, ',');
            
            // Convert the numeric string to short using std::stoi
            contact.address.streetNumber = static_cast<short>(stoi(streetNumberStr));
            contact.address.areaCode = static_cast<short>(stoi(areaCodeStr));
            
            // Remove quotes from field if there are any
            contact.fullName = contact.fullName.substr(1, contact.fullName.length() - 2);
            contact.phoneNumber = contact.phoneNumber.substr(1, contact.phoneNumber.length() - 2);
            contact.email = contact.email.substr(1, contact.email.length() - 2);
            contact.address.streetName = contact.address.streetName.substr(1, contact.address.streetName.length() - 2);
            contact.address.city = contact.address.city.substr(1, contact.address.city.length() - 2);
            contact.address.state = contact.address.state.substr(1, contact.address.state.length() - 2);
            
            addressBook.contacts.push_back(contact);
        }
        inFile.close();
        cout << "Contacts loaded from " << filename << endl;
    }
    
    //function manages the user interface to select what they want to do in the address book program
    void manageAddressBook(Address& addressBook){
        int choice = 0;
        do{
            // Menu option
            cout << AddContactMenu << ". Add Contact" << endl;
            cout << DisplayContactMenu << ". View Contact" << endl;
            cout << SearchContactMenu << ". Search Contact" << endl;
            cout << DeleteContactMenu << ". Delete Contact" << endl;
            cout << EditContactMenu << ". Edit Contact" << endl;
            cout << SaveToFileMenu << ". Save to File" << endl;
            cout << LoadFromFileMenu << ". Load from File" << endl;
            cout << Exit << ". Exit" << endl;
            
            // Get user's choice
            cin >> choice;
            
            switch (choice){
                case AddContactMenu:{
                    Contact newContact;
                    cout << "Enter new contacts full name: " << endl;
                    cin.ignore(); //clear newline
                    
                    getline(cin, newContact.fullName);
                    
                    cout << "Enter new contacts phone number" << endl;
                    getline(cin, newContact.phoneNumber);
                    
                    cout << "Enter new contacts email" << endl;
                    getline(cin, newContact.email);
                    
                    cout << "Enter new contacts street number:" << endl;
                    cin >> newContact.address.streetNumber;
                    
                    cout << "Enter new contacts street name:" << endl;
                    cin.ignore();
                    getline(cin, newContact.address.streetName);
                    
                    cout << "Enter new contacts city:" << endl;
                    getline(cin, newContact.address.city);
                    
                    cout << "Enter new contacts state:" << endl;
                    getline(cin, newContact.address.state);
                    
                    cout << "Enter new contacts area code:" << endl;
                    cin >> newContact.address.areaCode;
                    
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
                case SaveToFileMenu:{
                    string filename;
                    cout << "Enter filename to save the address book: ";
                    cin >> filename;
                    saveToFile(addressBook, filename);
                    break;
                }

                case LoadFromFileMenu:{
                    string filename;
                    cout << "Enter filename to load the address book: ";
                    cin >> filename;
                    loadFromFile(addressBook, filename);
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
