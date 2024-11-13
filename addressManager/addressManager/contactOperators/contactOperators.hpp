#ifndef contactOperators_hpp
#define contactOperators_hpp

#include "contact.h"
#include <ostream>

using std::ostream;


namespace addressBookManagement{
    //Overload << operator to easily print out the contact details in a formatted way
    ostream& operator << (ostream& stream, const Contact& contact);
}

#endif
