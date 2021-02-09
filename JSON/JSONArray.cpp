//
// Created by a404m on 2/5/21.
//

#include "JSONArray.h"
#include <iostream>
#include "JSONObject.h"
void deleteSpaces(std::string&);

JSONArray::JSONArray() {
    stringHolder.clear();
    boolHolder.clear();
    numberHolder.clear();
    jsonArrayHolder.clear();
    jsonObjectHolder.clear();
    typeHolder.clear();
}

JSONArray::JSONArray(std::string str) {
    deleteSpaces(str);

    if(str[0] == '[' && str[str.size()-1] == ']'){
        str.erase(str.size()-1,1);
        str.erase(0,1);
    }
    else{
        printERR("no []");
    }

    std::string value{};

    JSONArrayType jsonArrayType;
    bool isInString = false;
    unsigned int in = 0;

    for(unsigned long long i = 0;i < str.size();i++){
        if(str[i] == '\"' && (i == 0 || str[i-1] != '\\'))
            isInString = !isInString;

        if(isInString)
            goto COLLECT;

        if(str[i] == '[' || str[i] == '{')
            in++;
        else if(str[i] == ']' || str[i] == '}')
            in--;

        if(in == 0 && (str[i] == ',' || i+1 == str.size())){
            if(i+1 == str.size())
                value += str[i];

            if(value[0] == '\"' || value[0] == '\''){
                if(value[value.size()-1] != value[0] || value[value.size()-2] == '\\')
                    printERR("bad string \"" + value + '\"');

                value.erase(value.size()-1,1);
                value.erase(0,1);

                jsonArrayType.type = JSON_STRING;
                jsonArrayType.index = stringHolder.size();

                stringHolder.push_back(value);
            }
            else if(isdigit(value[value.size()-1])){
                jsonArrayType.type = JSON_NUMBER;
                jsonArrayType.index = numberHolder.size();

                numberHolder.push_back(std::stold(value));
            }
            else if(value == "true" || value == "false"){
                jsonArrayType.type = JSON_BOOLEAN;
                jsonArrayType.index = boolHolder.size();

                boolHolder.push_back(value == "true");
            }
            else if(value[0] == '['){
                jsonArrayType.type = JSON_ARRAY;
                jsonArrayType.index = jsonArrayHolder.size();

                jsonArrayHolder.emplace_back(value);
            }
            else if(value[0] == '{'){
                jsonArrayType.type = JSON_OBJECT;
                jsonArrayType.index = jsonObjectHolder.size();

                jsonObjectHolder.emplace_back(value);
            }
            else if(value == "null"){
                jsonArrayType.type = JSON_NULL;
            }
            else{
                printERR("unknown value \"" + value + '\"');
            }

            typeHolder.push_back(jsonArrayType);
            value.clear();
            continue;
        }

        COLLECT:
        value += str[i];

        /*if(str[i] == '['){
            unsigned short in = 1;
            begin = i;
            for(i++;i < str.size() || in != 0;i++){
                if(str[i] == '['){
                    in++;
                }else if(str[i] == ']'){
                    in--;
                }
            }
            auto temp = str.substr(begin,i-begin);

            jsonArrayType.index = jsonArrayHolder.size();
            jsonArrayType.type = JSON_ARRAY;

            jsonArrayHolder.emplace_back(temp);
            typeHolder.push_back(jsonArrayType);
        }
        else if((str[i] == ',' && (!isInString)) || i+1 == str.size()){
            auto temp = str.substr(begin,i-begin + ((i+1 == str.size())?1:0));
            if((temp[0] == '\"' && temp[temp.size()-1] == '\"') || (temp[0] == '\'' && temp[temp.size()-1] == '\'')){
                if(temp[temp.size()-2] == '\\'){
                    printERR("no closing string at " + std::to_string(i));
                }else{
                    temp.erase(temp.size()-1,1);
                    temp.erase(0,1);

                    jsonArrayType.index = stringHolder.size();
                    jsonArrayType.type = JSON_STRING;

                    stringHolder.push_back(temp);
                    typeHolder.push_back(jsonArrayType);
                }
            }
            else if(isdigit(temp[temp.size()-1])){
                jsonArrayType.index = numberHolder.size();
                jsonArrayType.type = JSON_NUMBER;

                numberHolder.push_back(std::stold(temp));
                typeHolder.push_back(jsonArrayType);
            }
            else if(temp == "true" || temp == "false"){
                jsonArrayType.index = boolHolder.size();
                jsonArrayType.type = JSON_BOOLEAN;

                boolHolder.push_back(temp == "true");
                typeHolder.push_back(jsonArrayType);
            }
            else if(temp == "null"){
                jsonArrayType.index = 0;
                jsonArrayType.type = JSON_NULL;
                typeHolder.push_back(jsonArrayType);
            }
            else{
                printERR("unknown value \"" + temp + "\" at " + std::to_string(i+1*//*1 for deleted*//*) + " '" + str[i] + '\'');
            }
            begin = i+1;
        }*/
    }
}

JSONArray::JSONArray(const JSONArray &jsonArray) = default;

JSONArray::~JSONArray() {
    stringHolder.clear();
    boolHolder.clear();
    numberHolder.clear();
    jsonArrayHolder.clear();
    jsonObjectHolder.clear();
    typeHolder.clear();
}

std::string JSONArray::toString() const {
    std::string result{};
    result += '[';

    for(auto type : typeHolder){
        switch(type.type){
            case JSON_NULL:
                result += "null";
                break;
            case JSON_BOOLEAN:
                result += (boolHolder[type.index]?"true":"false");
                break;
            case JSON_NUMBER:
                result += std::to_string(numberHolder[type.index]);
                break;
            case JSON_STRING:
                result += '\"' + stringHolder[type.index] + '\"';
                break;
            case JSON_ARRAY:
                result += jsonArrayHolder[type.index].toString();
                break;
            case JSON_OBJECT:
                result += jsonObjectHolder[type.index].toString();
                break;
            default:
                printERR("unknown type " + std::to_string(type.type));
        }
        result += ',';
    }

    result[result.size()-1] = ']';//it was ','
    return result;
}

//private
void JSONArray::printERR(const std::string &error) {
    std::cerr << "JSONArrayERR: " << error << std::endl;
    exit(-1);
}

JSONArray &JSONArray::operator=(const JSONArray &jsonArray) = default;

TheJSONType JSONArray::getTypeAt(const unsigned long long int &i) {
    return typeHolder[i].type;
}

bool JSONArray::getBoolAt(const unsigned long long int &i) {
    if(typeHolder[i].type != JSON_BOOLEAN)
        printERR("index " + std::to_string(i) + " is not bool");
    return boolHolder[typeHolder[i].index];
}

long double JSONArray::getNumberAt(const unsigned long long int &i) {
    if(typeHolder[i].type != JSON_NUMBER)
        printERR("index " + std::to_string(i) + " is not number");
    return numberHolder[typeHolder[i].index];
}

std::string JSONArray::getStringAt(const unsigned long long int &i) {
    if(typeHolder[i].type != JSON_STRING)
        printERR("index " + std::to_string(i) + " is not string");
    return stringHolder[typeHolder[i].index];
}

JSONArray JSONArray::getJSONArrayAt(const unsigned long long int &i) {
    if(typeHolder[i].type != JSON_ARRAY)
        printERR("index " + std::to_string(i) + " is not JSONArray");
    return jsonArrayHolder[typeHolder[i].index];
}
