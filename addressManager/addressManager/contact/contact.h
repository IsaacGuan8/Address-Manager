#ifndef contact_h
#define contact_h

#include <string>

using std::string;

//struct to store individual contact information
struct Contact{
    string fullName; // Full name of contact
    string phoneNumber; // Phone number of contact (ex. "510-346-2367")
    string email; // Email address of the contact (ex. "example@example.com")
    string streetAddress; // Physical address of the contact (ex. "321 orange street)
};

#endif
