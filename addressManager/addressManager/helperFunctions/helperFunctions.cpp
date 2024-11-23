// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <limits>

// Project-specific includes
#include "contact.h"
#include "address.h"

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

    // Helper function to compare contacts names
    bool compareByName(const unique_ptr<Contact>& a, const unique_ptr<Contact>& b){
        return a->fullName < b->fullName; // Dereference unique_ptr and compare fullName
    }
};
