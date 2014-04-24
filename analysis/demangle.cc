#include "demangle.hh"
#include <typeinfo>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);

    return (status==0) ? res : name ;
}

#else

// does nothing if not g++
std::string demangle(const char* name)
{
    return name;
}


#endif


