// Standard C++ libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <string>
#include <algorithm>
#include <utility>

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
            cout << endl;
            cout << "Contacts in the address book:" << endl;
            // Access the underlying array with &addressBook.contacts[0] to perform pointer arithmetic
            const unique_ptr<Contact>* ptr = &addressBook.contacts[0];

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
            helper::displayEditMenu(contactToEdit);
            
            int choice;
            cout << "Enter your choice:" << endl;
            
            // Validate user input
            while(!(cin >> choice) || choice < helper::toInt(EditContactMenu::EditFullName) || choice > helper::toInt(EditContactMenu::ExitAndSave)){
                // Clear the error flag and discard invalid input
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid choice, input another choice: " << endl;
            }

            editChoice = static_cast<EditContactMenu>(choice);
            
            // Process menu choice for editing
            switch(editChoice){
                case EditContactMenu::EditFullName:
                    contactToEdit->fullName = helper::getStringInput("Enter new full name:");
                    break;
                    
                case EditContactMenu::EditPhoneNumber:
                    contactToEdit->phoneNumber = helper::getStringInput("Enter new phone number:");
                    break;
                    
                case EditContactMenu::EditEmail:
                    contactToEdit->email = helper::getValidEmail("Enter new email:");
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
                    contactToEdit->address.city = helper::getStringInput("Enter new city:");
                    break;
                    
                case EditContactMenu::EditState:
                    contactToEdit->address.state = helper::getStateInput("Enter new state:");
                    break;
                    
                case EditContactMenu::EditAreaCode:
                    contactToEdit->address.areaCode = helper::getIntInput("Enter new area code:");
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
        
        // Check if the file path ends with ".csv"
        if (filepath.size() < 4 || filepath.substr(filepath.size() - 4) != ".csv"){
            cout << "Load unsuccessful. Please ensure the file has a '.csv'. Return to Menu." << endl;
            return;
        }
        
        ofstream outFile(filepath);

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
        cout << "Contacts have been successfully saved to: " << filepath << endl;
    }

    // Function to load address book from file
    void loadFromFile(Address& addressBook, const string& filepath){
        
        // Check if the file path ends with ".csv"
        if (filepath.size() < 4 || filepath.substr(filepath.size() - 4) != ".csv"){
            cout << "Save unsuccessful. Please ensure the file has '.csv'. Return to Menu." << endl;
            return;
        }
        
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
        cout << "Successfully loaded from file path " << filepath << endl;
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
        
        do{
            cout << "Below are the operation you can perform." << endl;
            cout << "Choose one using the numbers indicated." << endl;
            // Menu option
            helper::displayMenu();
            
            // Get user's choice
            int inputChoice;
            cout << "Enter your choice: " << endl;
            
            // Validate user input
            while(!(cin >> inputChoice) || inputChoice < helper::toInt(MenuChoice::AddContactMenu) || inputChoice > helper::toInt(MenuChoice::Exit)){
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
                    cout << "Enter a full name to search for in address book:" << endl;
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
                    break;
                }

                case MenuChoice::LoadFromFileMenu:{
                    string filepath;
                    cout << "Enter filename to load the address book: (formatted as .../name.csv)" << endl;
                    cin.ignore();
                    getline(cin, filepath);
                    loadFromFile(addressBook, filepath);
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
