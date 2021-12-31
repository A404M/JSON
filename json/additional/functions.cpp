#include "functions.hpp"
#include "../json-array/JSONArray.hpp"
#include "../json-object/JSONObject.hpp"

namespace json{
    extern Object getNextValue(std::string::const_iterator &begin,std::string::const_iterator end){
        jumpAcrossSpaces(begin,end);
        auto &c = *begin;
        switch(c){
            case '\"':
                return Object(getNextString(begin,end));
            case 't':
            case 'f':
                return Object(getNextBool(begin,end));
            case 'n':
                if(isNextNull(begin,end)){
                    return Object();
                }
                break;
            case '[':
                return Object(JSONArray(begin,end));
            case '{':
                return Object(JSONObject(begin,end));
            case '+':
            case '-':
                goto NUMBER;
            default:
                if(isdigit(c)){
                    NUMBER:
                    return Object(getNextDouble(begin,end));
                }
                throw std::runtime_error("getValue");
        }
        throw std::runtime_error("getValue");
    }

    extern std::string getNextString(std::string::const_iterator &begin,std::string::const_iterator end){
        std::string result;
        auto it = begin;
        if(*it != '\"'){
            throw std::runtime_error("getNextString");
        }
        ++it;
        for(;it < end;++it){
            if(*it == *begin){
                begin = ++it;
                return result;//without string markers
            }else if(*it == '\\'){
                ++it;
                switch(*it){
                    case 'a':
                        result += '\a';
                        break;
                    case 'b':
                        result += '\b';
                        break;
                    case 'e':
                        result += '\e';//escape
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
                    case 'v':
                        result += '\v';
                        break;
                    case '\\':
                        result += '\\';
                        break;
                    case '\"':
                        result += '\"';
                        break;
                    case '\'':
                        result += '\'';
                        break;
                    case '?':
                        result += '\?';//? character
                        break;
                    case 'u':
                        ++it;
                        result += unicodeToUTF8(hexToDecimal(std::string(it,it+4)));
                        it += 4;
                        break;
                }
            }else{
                result += *it;
            }
        }
        throw std::runtime_error("no closing \"");
    }

    extern long double getNextDouble(std::string::const_iterator &begin,std::string::const_iterator end){
        char *p;
        auto pbegin = &*begin;
        auto result = std::strtold(pbegin,&p);
        if(end-begin <= p-pbegin){
            throw std::runtime_error("excepted ','");
        }
        begin += p-pbegin;
        return result;
    }

    extern bool getNextBool(std::string::const_iterator &begin,std::string::const_iterator end){
        if(*begin == 't'){
            if(*++begin == 'r' && *++begin == 'u' && *++begin == 'e'){
                ++begin;
                if(begin >= end)
                    throw std::runtime_error("getNextBool");
                return true;
            }
        }else if(*begin == 'f'){
            if(*++begin == 'a' && *++begin == 'l' && *++begin == 's' && *++begin == 'e'){
                ++begin;
                if(begin >= end)
                    throw std::runtime_error("getNextBool");
                return false;
            }
        }
        throw std::runtime_error("unknown keywrod");
    }

    extern bool isNextNull(std::string::const_iterator &begin,std::string::const_iterator end){
        if(*begin == 'n' && *++begin == 'u' && *++begin == 'l' && *++begin == 'l'){
            ++begin;
            if(begin >= end)
                throw std::runtime_error("getNextBool");
            return true;
        }
        throw std::runtime_error("unknown keyword");
    }
    extern void jumpAcrossSpaces(std::string::const_iterator &begin,std::string::const_iterator end){
        for(;begin < end && std::isspace(*begin);++begin);
    }
    extern std::string unicodeToUTF8(unsigned int codepoint){
        std::string out;

        if (codepoint <= 0x7f)
            out.append(1, static_cast<char>(codepoint));
        else if (codepoint <= 0x7ff)
        {
            out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }
        else if (codepoint <= 0xffff)
        {
            out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }
        else
        {
            out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
        }
        return out;
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