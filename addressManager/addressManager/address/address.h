#ifndef address_h
#define address_h

// Standard C++ libraries
#include <vector>

// Project-specific includes
#include "contact.h"

using std::vector, std::unique_ptr;

// Structure to store vector for contacts
struct Address{
    vector<unique_ptr<Contact>> contacts;
};

#endif
