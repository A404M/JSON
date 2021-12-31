#ifndef JSON_ADDITIONAL_FUNCTIONS_HPP
#define JSON_ADDITIONAL_FUNCTIONS_HPP

#include <string>
#include <stdexcept>
#include "../object/Object.hpp"
#include "macros.hpp"

namespace json{
    extern Object getNextValue(std::string::const_iterator &begin,std::string::const_iterator end);
    extern std::string getNextString(std::string::const_iterator &begin,std::string::const_iterator end);
    extern long double getNextDouble(std::string::const_iterator &begin,std::string::const_iterator end);
    extern bool getNextBool(std::string::const_iterator &begin,std::string::const_iterator end);
    extern bool isNextNull(std::string::const_iterator &begin,std::string::const_iterator end);
    extern void jumpAcrossSpaces(std::string::const_iterator &begin,std::string::const_iterator end);
    extern std::string unicodeToUTF8(unsigned int codepoint);
    extern unsigned int hexToDecimal(const std::string &hex);
}//namespace json


#endif//JSON_ADDITIONAL_FUNCTIONS_HPP