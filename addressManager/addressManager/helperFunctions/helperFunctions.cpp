// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>
#include <cctype>

// Project-specific includes
#include "contact.h"
#include "address.h"
#include "menu.h"
#include "editContactMenu.h"

using std::string, std::to_string, std::endl, std::cout, std::cin, std::streamsize, std::numeric_limits, std::stringstream;

namespace helper{
    // Function to make sure input is a string
    int getIntInput(const string& prompt){
        int input;
        while(true){
            cout << prompt << endl;
            cin >> input;
            if(cin.fail()){ // Check if input failed
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter an integer:" << endl;
            }else{
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear extra input
                return input;
            }
        }
    }

    // Function to make sure input is a short integer
    short getShortInput(const string& prompt){
        int input;
        while(true){
            cout << prompt << endl;
            cin >> input;
            if(cin.fail() || input < numeric_limits<short>::min() || input > numeric_limits<short>::max()){ // Check if input failed
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter an short integer:" << endl;
            }else{
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear extra input
                return input;
            }
        }
    }

    // Function to make sure input is a string
    string getStringInput(const string& prompt){
        string input;
        while(true){
            cout << prompt << endl;
            if(cin.peek() == '\n') cin.ignore();
            getline(cin, input);
            if(input.empty()){
                cout << "Input cannot be empty. Please enter a valid string:" << endl;
            }else{
                return input;
            }
        }
    }

    // Function to make sure input is a state abbreviated (2 initials)
    string getStateInput(const string& prompt){
        string state;
        while(true){
            cout << prompt << endl;
            if(cin.peek() == '\n') cin.ignore();
            getline(cin, state);
            if(state.length() == 2){
                // Automatically capitalize state initials
                state[0] = toupper(state[0]);
                state[1] = toupper(state[1]);
                return state;
            }else{
                cout << "Invalid state. Please enter a 2-letter state code:" << endl;
            }
        }
    }

    // Function to make sure input is an email (has an @)
    string getValidEmail(const string& prompt){
        string email;
        while(true){
            cout << prompt << endl;
            getline(cin, email);
            
            // Convert email to c-style string
            const char* cstr = email.c_str();
            
            if(strchr(cstr, '@') != nullptr){
                return email;
            }else{
                cout << "Invalid email. Please enter an '@' symbol in the email." << endl;
            }
        }
    }

    // Helper function to find contact for editContact
    Contact* findContactByName(Address& addressBook, const string& name){
        for(auto& contactPtr : addressBook.contacts){
            if(contactPtr->fullName == name){
                return contactPtr.get(); // Return raw pointer from unique_ptr
            }
        }
        return nullptr;
    }

    // Helper function to trim quotes when loading files
    string removeQuotes(const string& str){
        string result = str;
        if(!result.empty() && result.front() == '"' && result.back() == '"'){
            result = result.substr(1, result.size() - 2);
        }
        return result;
    }
    
    // Helper function to compare contacts names
    bool compareByName(const unique_ptr<Contact>& a, const unique_ptr<Contact>& b){
        return a->fullName < b->fullName; // Dereference unique_ptr and compare fullName
    }

    // Helper function to get the integer value of an enum for manageAddressBook function
    int toInt(MenuChoice choice){
        return static_cast<int>(choice);
    }

    // Helper function to get the integer value of an enum overloaded for editContact function
    int toInt(EditContactMenu choice){
        return static_cast<int>(choice);
    }
    
    // Display the menu for user in the manageAddressBook function
    void displayMenu(){
        cout << toInt(MenuChoice::AddContactMenu) << ". Add Contact" << endl;
        cout << toInt(MenuChoice::DisplayContactMenu) << ". View Contact" << endl;
        cout << toInt(MenuChoice::SearchContactMenu) << ". Search Contact" << endl;
        cout << toInt(MenuChoice::DeleteContactMenu) << ". Delete Contact" << endl;
        cout << toInt(MenuChoice::EditContactMenu) << ". Edit Contact" << endl;
        cout << toInt(MenuChoice::SaveToFileMenu) << ". Save to File" << endl;
        cout << toInt(MenuChoice::LoadFromFileMenu) << ". Load from File" << endl;
        cout << toInt(MenuChoice::SortContactByNameMenu) << ". Sort Contacts Alphabetically" << endl;
        cout << toInt(MenuChoice::Exit) << ". Exit" << endl;
    }

    // Display the menu for user in the editContact function
    void displayEditMenu(Contact* contactToEdit){
        cout << "Editing Contact: " << contactToEdit->fullName << endl;
        cout << toInt(EditContactMenu::EditFullName) << ". Edit Full Name" << endl;
        cout << toInt(EditContactMenu::EditPhoneNumber) << ". Edit Phone Number" << endl;
        cout << toInt(EditContactMenu::EditEmail) << ". Edit Email" << endl;
        cout << toInt(EditContactMenu::EditStreetAddress) << ". Edit Street Address" << endl;
        cout << toInt(EditContactMenu::EditCity) << ". Edit City" << endl;
        cout << toInt(EditContactMenu::EditState) << ". Edit State" << endl;
        cout << toInt(EditContactMenu::EditAreaCode) << ". Edit Area Code" << endl;
        cout << toInt(EditContactMenu::ExitAndSave) << ". Save and Exit Edit Menu" << endl;
        
    }
};
