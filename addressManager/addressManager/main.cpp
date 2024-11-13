#include <iostream>
#include "addressBookFunctions/addressBookFunctions.hpp"
#include "address/address.h"

using namespace std;

int main() {
    Address address;
    addressBookManagement::manageAddressBook(address);
    
    return 0;
}
