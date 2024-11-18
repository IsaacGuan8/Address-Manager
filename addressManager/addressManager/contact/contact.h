#ifndef contact_h
#define contact_h

#include <string>

using std::string;

// Struct to store address details
struct AddressDetails{
    short streetNumber;
    string streetName;
    string city;
    string state;
    short areaCode;
};

// Struct to store individual contact information
struct Contact{
    string fullName;
    string phoneNumber;
    string email;
    AddressDetails address; // Nest AddressDetails struct
};

#endif
