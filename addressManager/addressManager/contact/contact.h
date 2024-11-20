#ifndef contact_h
#define contact_h

// Standard C++ libraries
#include <string>

using std::string;

// Struct to store location details
struct LocationDetails{
    string streetAddress;
    string city;
    string state;
    int areaCode;
};

// Struct to store individual contact information
struct Contact{
    string fullName;
    string phoneNumber;
    string email;
    LocationDetails address; // Nested AddressDetails struct
};

#endif
