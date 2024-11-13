#include "contact.h"
#include <ostream>

using std::ostream;

namespace addressBookManagement{
    ostream& operator<<(ostream& stream, const Contact& contact){
        stream << "Name: " << contact.fullName << "\n"
        << "Phone: " << contact.phoneNumber << "\n"
        << "Email: " << contact.email << "\n"
        << "Address: " << contact.streetAddress << "\n";
        return stream;
    }
}
