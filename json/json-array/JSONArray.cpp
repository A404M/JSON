#include "JSONArray.hpp"
#include "../additional/functions.hpp"
#include "../json-object/JSONObject.hpp"

using namespace json;

JSONArray::JSONArray() : holder() {
    //empty
}
JSONArray::JSONArray(const std::string &str) {
    auto begin = str.begin(), end = str.end();

    jumpAcrossSpaces(begin,end);
    if(*begin != '[')
        throw std::runtime_error("JSONArray::JSONArray");

    jumpAcrossSpaces(begin,end);
    *this = JSONArray(begin,end);

    jumpAcrossSpaces(begin,end);
    if(begin != str.end())
        throw std::runtime_error("JSONArray::JSONArray");
}
JSONArray::JSONArray(std::string::const_iterator &begin,std::string::const_iterator end) : holder() {
    //holder.reserve(1024*1024);
    if(*++begin == ']'){
        ++begin;
        return;
    }
    goto AFTER_INC;//instead of --begin, ++begin
    //--begin;
    
    do{
        ++begin;
        AFTER_INC:
        getNextValue(begin, end);
        jumpAcrossSpaces(begin,end);
    }while(begin < end && *begin == ',');

    //holder.shrink_to_fit();

    if(*begin != ']'){
        throw std::runtime_error("excepted ','");
    }

    ++begin;
}

Object &JSONArray::operator[](size_type index) {
    return holder[index];
}

const Object &JSONArray::operator[](size_type index) const {
    return holder[index];
}

std::string JSONArray::toString() const {
    if(holder.empty()){
        return "[]";
    }
    std::string result = "[";
    for (const auto &obj : holder) {
        result += obj.toString();
        result += ',';
    }
    result.back() = ']';
    return result;
}

JSONArray::size_type JSONArray::size() const {
    return holder.size();
}

void JSONArray::getNextValue(std::string::const_iterator &begin,std::string::const_iterator end) {
    jumpAcrossSpaces(begin,end);
    auto c = *begin;
    switch(c){
        case '\"':
            holder.emplace_back(getNextString(begin, end));
            return;
        case 't':
            if(*++begin == 'r' && *++begin == 'u' && *++begin == 'e') {
                ++begin;
                holder.emplace_back(true);
                return;
            }
            break;
        case 'f':
            if(*++begin == 'a' && *++begin == 'l' && *++begin == 's' && *++begin == 'e') {
                ++begin;
                holder.emplace_back(false);
                return;
            }
            break;
        case 'n':
            if(*++begin == 'u' && *++begin == 'l' && *++begin == 'l'){
                ++begin;
                holder.emplace_back();//null
                return;
            }
            break;
        case '[':
            holder.emplace_back(JSONArray(begin, end));
            return;
        case '{':
            holder.emplace_back(JSONObject(begin, end));
            return;
        case '+':
        case '-':
            goto NUMBER;
        default:
            if(isDigit(c)) {
                NUMBER:
                holder.emplace_back(getNextDouble(begin, end));
                return;
            }
        break;
    }
    throw std::runtime_error("getValue");
}
