#include "contact.h"
#include <ostream>

using std::ostream, std::endl;

namespace addressBookManagement{
    ostream& operator<<(ostream& stream, const Contact& contact){
        stream << "Name: " << contact.fullName << endl;
        stream << "Phone: " << contact.phoneNumber << endl;
        stream << "Email: " << contact.email << endl;
        stream << "Address: " << contact.address.streetNumber << " " << contact.address.streetName << ", " << contact.address.city << ", " << contact.address.state << ", " << contact.address.areaCode << endl;
        return stream;
    }
}
