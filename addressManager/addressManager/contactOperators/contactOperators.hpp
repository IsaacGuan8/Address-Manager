#ifndef contactOperators_hpp
#define contactOperators_hpp

#include "contact.h"
#include <ostream>

using std::ostream;

namespace addressBookManagement{
    ostream& operator << (ostream& stream, const Contact& contact);
}

#endif
