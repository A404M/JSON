#include "functions.hpp"

namespace json{
    extern std::string getNextString(std::string::const_iterator &begin,std::string::const_iterator end){
        std::string result;
        ++begin;
        for(;begin < end; ++begin){
            auto c = *begin;
            if(c == '\"'){
                ++begin;
                return result;//without string markers
            }else if(c == '\\'){
                ++begin;
                switch(*begin){
                    case 'b':
                        result += '\b';
                        break;
                    case 'f':
                        result += '\f';
                        break;
                    case 'n':
                        result += '\n';
                        break;
                    case 'r':
                        result += '\r';
                        break;
                    case 't':
                        result += '\t';
                        break;
                    case '\\':
                        result += '\\';
                        break;
                    case '\"':
                        result += '\"';
                        break;
                    case 'u': {
                        auto tmp = ++begin;
                        unicodeToUTF8(hexToDecimal(std::string(tmp, begin += 4)), result);
                        break;
                    }
                    case '/':
                        result += '/';
                        break;
                    default:
                        throw std::runtime_error("getNextString");
                }
            }else{
                result += c;
            }
        }
        throw std::runtime_error("no closing \"");
    }

    extern long double getNextDouble(std::string::const_iterator &begin,std::string::const_iterator end){
        char *p;
        auto pbegin = &*begin;
        auto result = std::strtold(pbegin,&p);
        begin += p-pbegin;
        if(begin >= end)
            throw std::runtime_error("excepted ','");
        return result;
    }

    extern void jumpAcrossSpaces(std::string::const_iterator &begin,std::string::const_iterator end){
        for(;std::isspace(*begin) && begin < end;++begin);
    }

    extern bool isDigit(char c){
        return c >= '0' && c <= '9';
    }

    extern void unicodeToUTF8(unsigned int codepoint,std::string &out){
        if (codepoint <= 0x7f)
            out.append(1, static_cast<char>(codepoint));
        else if (codepoint <= 0x7ff){
            out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }else if (codepoint <= 0xffff){
            out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }else{
            out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }
    }
    extern unsigned int hexToDecimal(const std::string &hex){
        unsigned int result = 0,p = 1;
        for(const auto& ch : hex){
            auto c = toupper(ch);
            if(c >= '0' && c <= '9'){
                result += (c-'0')*p;
            }else if(c >= 'A' && c <= 'F'){
                result += (c-'A')*10*p;
            }else{
                throw std::runtime_error("hexToDecimal");
            }
            p *= 16;
        }
        return result;
    }
}//namespace json
