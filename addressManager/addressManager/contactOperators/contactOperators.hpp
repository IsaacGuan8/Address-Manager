#ifndef contactOperators_hpp
#define contactOperators_hpp

// Standard C++ libraries
#include <ostream>

// Project-specific includes
#include "contact.h"

using std::ostream;

namespace addressBookManagement{
    ostream& operator << (ostream& stream, const Contact& contact);
}

#endif
