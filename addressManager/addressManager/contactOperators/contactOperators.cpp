// Standard C++ libraries
#include <ostream>

// Project-specific includes
#include "contact.h"
#include "helperFunctions.hpp"

using std::ostream, std::endl;

namespace addressBookManagement{
    //Overload << operator to easily print out the contact details in a formatted way
    ostream& operator<<(ostream& stream, const Contact& contact){
        stream << "Name: " << contact.fullName << endl;
        stream << "Phone: " << contact.phoneNumber << endl;
        stream << "Email: " << contact.email << endl;
        stream << "Street Address: " << contact.address.streetAddress << ", " << contact.address.city << ", " << contact.address.state << " " << contact.address.areaCode << endl;
        return stream;
    }
}
