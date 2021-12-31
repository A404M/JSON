#include "JSONObject.hpp"
#include "../additional/functions.hpp"
#include "../json-array/JSONArray.hpp"

using namespace json;

JSONObject::JSONObject() : holder() {
    //empty
}

JSONObject::JSONObject(const std::string &str) {
    auto begin = str.begin();
    *this = JSONObject(begin,str.end());
}

JSONObject::JSONObject(std::string::const_iterator &begin,std::string::const_iterator end) {
    if(*begin != '{'){
        throw std::runtime_error("JSONObject::JSONObject");
    }
    if(*(++begin) == '}'){
        ++begin;
        return;
    }
    goto AFTER_INC;//instead of --begin, ++begin
    //--begin;

    do{
        ++begin;
        AFTER_INC:
        getNextValue(begin,end);
        jumpAcrossSpaces(begin,end);
    }while(begin < end && *begin == ',');

    if(*begin != '}'){
        throw std::runtime_error("excepted ','");
    }

    ++begin;
}

Object &JSONObject::operator[](const std::string &key){
    return holder.at(key);
}

const Object &JSONObject::operator[](const std::string &key) const {
    return holder.at(key);
}

std::string JSONObject::toString() const {
    if(holder.empty()){
        return "{}";
    }
    std::string result = "{";

    for(const auto &pair : holder){
        result += '\"';
        result += pair.first;
        result += '\"';
        result += ':';
        result += pair.second.toString();
        result += ',';
    }

    result.back() = '}';

    return result;
}

JSONObject::size_type JSONObject::size() const {
    return holder.size();
}

void JSONObject::getNextValue(std::string::const_iterator &begin,std::string::const_iterator end) {
    jumpAcrossSpaces(begin,end);
    std::string key = getNextString(begin,end);
    if(*begin != ':')
        throw std::runtime_error("excepted ':'");
    ++begin;
    jumpAcrossSpaces(begin,end);
    auto c = *begin;
    switch(c){
        case '\"':
            holder.emplace(key,getNextString(begin,end));
            return;
        case 't':
        case 'f':
            holder.emplace(key,getNextBool(begin,end));
            return;
        case 'n':
            if(isNextNull(begin,end)){
                holder.emplace(key,nullptr);
                return;
            }
        case '[':
            holder.emplace(key,JSONArray(begin,end));
            return;
        case '{':
            holder.emplace(key,JSONObject(begin,end));
            return;
        case '+':
        case '-':
            goto NUMBER;
        default:
            if(isDigit(c)){
                NUMBER:
                holder.emplace(key,getNextDouble(begin,end));
                return;
            }
    }
    throw std::runtime_error("getValue");
}
