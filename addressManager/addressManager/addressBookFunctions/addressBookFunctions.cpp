// Standard C++ libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <string>

// Project-specific includes
#include "address.h"
#include "menu.h"
#include "contact.h"
#include "editContactMenu.h"
#include "contactOperators.hpp"
#include "helperFunctions.hpp"


using std::cout, std::endl, std::cin, std::string, std::getline, std::ifstream, std::ofstream, std::remove_if, std::stringstream, std::make_unique, std::numeric_limits, std::to_string, std::sort, std::to_string;
namespace addressBookManagement{
    //function to add in a contact into addressbook
    void addContact(Address& addressBook){
        Contact newContact;
        
        newContact.fullName = helper::getStringInput("Enter contact's full name:");
        newContact.phoneNumber = helper::getStringInput("Enter new contact's phone number:");
        newContact.email = helper::getValidEmail("Enter new contact's email(must include @ sign to be valid):");
        
        short streetNumber = helper::getShortInput("Enter new contact's street number:");
        string streetName = helper::getStringInput("Enter new contact's street name:");
        
        // Concatenate street number and street name together to store it in the address book
        newContact.address.streetAddress = to_string(streetNumber) + " " + streetName;
        
        newContact.address.city = helper::getStringInput("Enter new contact's city:");
        newContact.address.state = helper::getStateInput("Enter new contact's state (in abreviated form with two initials):");
        newContact.address.areaCode = helper::getIntInput("Enter new contact's area code:");
        
        
        addressBook.contacts.push_back(make_unique<Contact>(newContact));
        cout << "Contact added sucessfully" << endl;
    }

    //function that displays all contacts in the addressbook, if empty it will notify the user
    void displayContacts(const Address& addressBook){
        if(addressBook.contacts.empty()){
            cout << "Address book is currently empty!" << endl;
        }else{
            cout << "Contacts in the address book:" << endl;
            // Access the underlying array with &addressBook.contacts[0] and perform pointer arithmetic
            const unique_ptr<Contact>* ptr = &addressBook.contacts[0]; // Get a pointer to the first contact

            for(size_t i = 0; i < addressBook.contacts.size(); ++i){
                // Dereference the unique_ptr to get the Contact object pointer
                const Contact* contact = ptr[i].get(); // Use .get() to get the raw pointer from unique_ptr
                // Check if the contact is valid
                if(contact){
                    cout << "Contact " << i + 1 << ":" << endl;
                    cout << *contact << endl;
                    cout << "---------------------------" << endl;
                }
            }
        }
    }
    
    //function to search for a contact by name and print details
    void searchContact(const Address& addressBook, const string& name){
        for(const auto& contact : addressBook.contacts){
            if(contact->fullName == name){
                cout << "Contact Found:" << endl;
                cout << *contact << endl;
                cout << "--------------------" << endl;
                return;
            }
        }
        cout << "Contact with name " << name << " is not in the address book" << endl;
    }
    
    // Function to delete contact by the name from address book
    void deleteContact(Address& addressBook, const string& name){
        // Use remove_if to find the contact by name and remove it from the vector
        auto it = remove_if(
            addressBook.contacts.begin(),
            addressBook.contacts.end(),
            [&name](const unique_ptr<Contact>& contactPtr){
                return contactPtr->fullName == name; // Deferance unique pointer to access Contact
            }
        );

        // If the contact is found, erase it from the vector to actually delete it
        if(it != addressBook.contacts.end()){
            addressBook.contacts.erase(it, addressBook.contacts.end());
            cout << "Contact deleted." << endl;
        }else{
            cout << "Contact not found." << endl;
        }
    }

    // Function that presents a menu to edit an existing contact
    void editContact(Contact* contactToEdit){
        EditContactMenu editChoice = EditContactMenu::ExitAndSave; // Explicitly initialize to a valid value
        
        do{
            // Display Menu
            cout << "Editing Contact: " << contactToEdit->fullName << endl;
            cout << static_cast<int>(EditContactMenu::EditFullName) << ". Edit Full Name" << endl;
            cout << static_cast<int>(EditContactMenu::EditPhoneNumber) << ". Edit Phone Number" << endl;
            cout << static_cast<int>(EditContactMenu::EditEmail) << ". Edit Email" << endl;
            cout << static_cast<int>(EditContactMenu::EditStreetAddress) << ". Edit Street Address" << endl;
            cout << static_cast<int>(EditContactMenu::EditCity) << ". Edit City" << endl;
            cout << static_cast<int>(EditContactMenu::EditState) << ". Edit State" << endl;
            cout << static_cast<int>(EditContactMenu::EditAreaCode) << ". Edit Area Code" << endl;
            cout << static_cast<int>(EditContactMenu::ExitAndSave) << ". Save and Exit Edit Menu" << endl;
            
            int choice;
            cout << "Enter your choice:" << endl;
            
            // Validate user input
            while(!(cin >> choice) || choice <static_cast<int>(EditContactMenu::EditFullName) || choice > static_cast<int>(EditContactMenu::ExitAndSave)){
                // Clear the error flag and discard invalid input
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid choice, input another choice: " << endl;
            }

            editChoice = static_cast<EditContactMenu>(choice);
            
            // Process menu choice for editing
            switch(editChoice){
                case EditContactMenu::EditFullName:
                    cout << "Enter new full name: ";
                    getline(cin, contactToEdit->fullName);
                    break;
                    
                case EditContactMenu::EditPhoneNumber:
                    cout << "Enter new phone number: ";
                    getline(cin, contactToEdit->phoneNumber);
                    break;
                    
                case EditContactMenu::EditEmail:
                    cout << "Enter new email: ";
                    getline(cin, contactToEdit->email);
                    break;
                    
                case EditContactMenu::EditStreetAddress:
                    {
                        short streetNumber = helper::getShortInput("Enter new street number:");
                        string streetName = helper::getStringInput("Enter new street Name:");
                        
                        // Concatenate street number and street name and store it
                        contactToEdit->address.streetAddress = to_string(static_cast<int>(streetNumber)) + " " + streetName;
                    }
                    break;
                    
                case EditContactMenu::EditCity:
                    cout << "Enter new city: ";
                    cin >> contactToEdit->address.city;
                    break;
                    
                case EditContactMenu::EditState:
                    cout << "Enter new state: ";
                    cin >> contactToEdit->address.state;
                    break;
                    
                case EditContactMenu::EditAreaCode:
                    cout << "Enter new area code: ";
                    cin >> contactToEdit->address.areaCode;
                    break;
                    
                case EditContactMenu::ExitAndSave:
                    cout << "Exiting edit menu." << endl;
                    break;
                    
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }while(editChoice != EditContactMenu::ExitAndSave);
    }

    // Function to save address book to file
    void saveToFile(const Address& addressBook, const string& filepath){
        ofstream outFile(filepath); // Open the file at user specified path

        // Check if there are contacts to save
        if(addressBook.contacts.empty()){
            cout << "No contacts to save." << endl;
            return;
        }
    
        // Check if the file was opened successfully
        if(!outFile.is_open()){
            cout << "Error opening " << filepath << " for writing." << endl;
            return;
        }
    
        // Write CSV header
        outFile << "Full Name,Phone Number,Email,Full Address\n";
        
        // Loop through all contacts and write their details in CSV format
        for(const auto& contact : addressBook.contacts){
            outFile << '"' << contact->fullName << "\","
                    << '"' << contact->phoneNumber << "\","
                    << '"' << contact->email << "\","
                    << '"' << contact->address.streetAddress << "\","
                    << '"' << contact->address.city << "\","
                    << '"' << contact->address.state << "\","
                    << contact->address.areaCode << "\n";
        }

        outFile.close();
        cout << "Contacts have been saved to: " << filepath << endl;
    }

    // Function to load address book from file
    void loadFromFile(Address& addressBook, const string& filepath){
        ifstream inFile(filepath);
        
        // Check if the file was opened successfully
        if(!inFile.is_open()){
            cout << "Error opening " << filepath << " for reading." << endl;
            return;
        }
        
        string line;
        bool firstLine = true;
        
        while(getline(inFile, line)){
            // Makes sure we skip the header when reading
            if(firstLine){
                firstLine = false;
                continue;
            }
            
            stringstream ss(line);
            auto newContact = make_unique<Contact>();

            getline(ss, newContact->fullName, ',');
            newContact->fullName = helper::removeQuotes(newContact->fullName);

            getline(ss, newContact->phoneNumber, ',');
            newContact->phoneNumber = helper::removeQuotes(newContact->phoneNumber);

            getline(ss, newContact->email, ',');
            newContact->email = helper::removeQuotes(newContact->email);

            getline(ss, newContact->address.streetAddress, ',');
            newContact->address.streetAddress = helper::removeQuotes(newContact->address.streetAddress);

            getline(ss, newContact->address.city, ',');
            newContact->address.city = helper::removeQuotes(newContact->address.city);

            getline(ss, newContact->address.state, ',');
            newContact->address.state = helper::removeQuotes(newContact->address.state);

            ss >> newContact->address.areaCode;
            
            addressBook.contacts.push_back(std::move(newContact));
        }
        inFile.close();
    }

    // Function to sort full names Alphabetically
    void sortContactsByName(vector<unique_ptr<Contact>>& contacts){
        // Use the compareByName function to sort
        sort(contacts.begin(), contacts.end(), helper::compareByName);
    }

    // Function manages the user interface to select what they want to do in the address book program
    void manageAddressBook(Address& addressBook){
        MenuChoice choice = MenuChoice::Exit; // Explicitly initialize to a valid value
        
        cout << "Welcome to the address manager system!" << endl;
        cout << "Below are the operation you can perform." << endl;
        cout << "Choose one using the numbers indicated." << endl;
        do{
            // Menu option
            cout << static_cast<int>(MenuChoice::AddContactMenu) << ". Add Contact" << endl;
            cout << static_cast<int>(MenuChoice::DisplayContactMenu) << ". View Contact" << endl;
            cout << static_cast<int>(MenuChoice::SearchContactMenu) << ". Search Contact" << endl;
            cout << static_cast<int>(MenuChoice::DeleteContactMenu) << ". Delete Contact" << endl;
            cout << static_cast<int>(MenuChoice::EditContactMenu) << ". Edit Contact" << endl;
            cout << static_cast<int>(MenuChoice::SaveToFileMenu) << ". Save to File" << endl;
            cout << static_cast<int>(MenuChoice::LoadFromFileMenu) << ". Load from File" << endl;
            cout << static_cast<int>(MenuChoice::SortContactByNameMenu) << ". Sort Contacts Alphabetically" << endl;
            cout << static_cast<int>(MenuChoice::Exit) << ". Exit" << endl;
            
            // Get user's choice
            int inputChoice;
            cout << "Enter your choice: " << endl;
            
            // Validate user input
            while(!(cin >> inputChoice) || inputChoice < static_cast<int>(MenuChoice::AddContactMenu) || inputChoice > static_cast<int>(MenuChoice::Exit)){
                // Clear the error flag and discard invalid input
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid choice, input another choice: " << endl;
            }
            
            // Convert integer input to enum
            choice = static_cast<MenuChoice>(inputChoice);
            
            // Process menu choice
            switch(choice){
                case MenuChoice::AddContactMenu:{
                    addContact(addressBook);
                    break;
                }
                    
                case MenuChoice::DisplayContactMenu:
                    displayContacts(addressBook);
                    break;
                    
                case MenuChoice::SearchContactMenu:{
                    string name;
                    cout << "Enter to to search for in address book:" << endl;
                    cin.ignore();
                    getline(cin, name);
                    searchContact(addressBook, name);
                    break;
                }
                    
                case MenuChoice::DeleteContactMenu:{
                    string name;
                    cout << "Enter the name of the contact to delete: " << endl;
                    cin.ignore();
                    getline(cin, name);
                    deleteContact(addressBook, name);
                    break;
                }
                    
                case MenuChoice::EditContactMenu:{
                    // Edit contact by name
                    string name = helper::getStringInput("Enter the name of the contact to edit:");

                    // Use helper function to find the contact
                    Contact* contactToEdit = helper::findContactByName(addressBook, name);
                    
                    // Check if the contact was found
                    if(contactToEdit){
                        editContact(contactToEdit);
                        cout << "Contact successfully edited." << endl;
                    }else{
                        cout << "Contact not found." << endl;
                    }
                    break;
                }
                    
                case MenuChoice::SaveToFileMenu:{
                    string filepath;
                    cout << "Enter full file path to save the address book (formatted as .../name.csv):" << endl;
                    cin.ignore();
                    getline(cin, filepath);
                    saveToFile(addressBook, filepath);
                    cout << "Successfully saved to file path " << filepath << endl;
                    break;
                }

                case MenuChoice::LoadFromFileMenu:{
                    string filepath;
                    cout << "Enter filename to load the address book: (formatted as .../name.csv)" << endl;
                    cin.ignore();
                    getline(cin, filepath);
                    loadFromFile(addressBook, filepath);
                    cout << "Successfully loaded from filepath " << filepath << endl;
                    break;
                }
                   
                case MenuChoice::SortContactByNameMenu:
                    sortContactsByName(addressBook.contacts);
                    cout << "Contacts sorted alphabetically." << endl;
                    break;
                    
                case MenuChoice::Exit:
                    cout << "Thank you for using the Address Book Management program" << endl;
                    break;
                    
                default:
                    cout << "Invalid choice, input another choice." << endl;
            }
        }while(choice != MenuChoice::Exit);
    }
}
