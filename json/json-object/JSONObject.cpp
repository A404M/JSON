#include "JSONObject.hpp"
#include "../additional/functions.hpp"
#include "../json-array/JSONArray.hpp"

using namespace json;

JSONObject::JSONObject() : holder() {
    //empty
}

JSONObject::JSONObject(const std::string &str) {
    auto begin = str.begin(),end = str.end();

    jumpAcrossSpaces(begin,end);
    if(*begin != '{')
        throw std::runtime_error("JSONObject::JSONObject");

    jumpAcrossSpaces(begin,end);
    *this = JSONObject(begin,end);

    jumpAcrossSpaces(begin,end);
    if(begin != str.end())
        throw std::runtime_error("JSONArray::JSONArray");
}

JSONObject::JSONObject(std::string::const_iterator &begin,std::string::const_iterator end) {
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

JSONObject::JSONObject(JSONObject &&jsonObject)  noexcept : holder(std::move(jsonObject.holder)){/*empty*/}

JSONObject &JSONObject::operator=(JSONObject &&jsonObject) {
    holder = std::move(jsonObject.holder);
    return *this;
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
    if(*begin != '\"')
        throw std::runtime_error("excepted '\"'");
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
            if(*++begin == 'r' && *++begin == 'u' && *++begin == 'e') {
                ++begin;
                holder.emplace(key,true);
                return;
            }
            break;
        case 'f':
            if(*++begin == 'a' && *++begin == 'l' && *++begin == 's' && *++begin == 'e') {
                ++begin;
                holder.emplace(key,true);
                return;
            }
            break;
        case 'n':
            if(*++begin == 'u' && *++begin == 'l' && *++begin == 'l'){
                ++begin;
                holder.emplace(key,nullptr);
                return;
            }
            break;
        case '[':
            holder.emplace(key,JSONArray(begin,end));
            return;
        case '{':
            holder.emplace(key,JSONObject(begin,end));
            return;
        case '+':
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            holder.emplace(key,getNextDouble(begin, end));
            return;
        default:
            break;
    }
    throw std::runtime_error("getValue");
}
