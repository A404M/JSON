//
// Created by a404m on 2/5/21.
//

#include "JSONObject.h"
#include <iostream>
#include "JSONArray.h"
void deleteSpaces(std::string&);

/*        if(str[i] == '['){
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

            std::cout << "temp = " << temp << std::endl;

            jsonObjectType.index = jsonArrayHolder.size();
            jsonObjectType.type = JSON_ARRAY;

            jsonArrayHolder.emplace_back(temp);
            if(isExist(name)){
                printERR(name + " is exist");
            }else{
                typeHolder[name] = jsonObjectType;
            }
        }

        if((!isInString) && (str[i] == ',' || i+1 == str.size())){
            auto temp = str.substr(begin,i-begin + ((i+1 == str.size())?1:0));
            unsigned long long sepIndex = 0,j = 0;
            for(;j < temp.size();j++){
                if(temp[j] == '\"' && (j == 0 || temp[j-1] != '\\'))
                    isInString = !isInString;

                if(temp[j] == ':' && (!isInString)){
                    sepIndex = j;
                }
            }
            if(sepIndex == 0)
                printERR("no : used in \"" + temp + "\" at range [" + std::to_string(begin) + ',' + std::to_string(begin+j) + "]");

            name = temp.substr(0,sepIndex);
            value = temp.substr(sepIndex+1,j-sepIndex-1);
            temp.clear();
            name = name.substr(1,name.size()-2);

            if((value[0] == '\"' && value[value.size()-1] == '\"') || (value[0] == '\'' && value[value.size()-1] == '\'')){
                if(value[value.size()-2] == '\\')
                    printERR("no closing string at " + std::to_string(begin+j));

                jsonObjectType.type = JSON_STRING;
                jsonObjectType.index = stringHolder.size();

                stringHolder.push_back(value.substr(1,value.size()-2));
            }else if(isdigit(value[value.size()-1])){
                jsonObjectType.type = JSON_NUMBER;
                jsonObjectType.index = numberHolder.size();

                numberHolder.push_back(std::stold(value));
            }else if(value == "true" || value == "false"){
                jsonObjectType.type = JSON_BOOLEAN;
                jsonObjectType.index = boolHolder.size();

                boolHolder.push_back(value == "true");
            }else if(value == "null"){
                jsonObjectType.type = JSON_NULL;
            }

            if(isExist(name)){
                printERR(name + " is exist");
            }else{
                typeHolder[name] = jsonObjectType;
            }

            begin = i+1;
        }*/

JSONObject::JSONObject() {
    boolHolder.clear();
    numberHolder.clear();
    stringHolder.clear();
    jsonArrayHolder.clear();
    jsonObjectHolder.clear();
    typeHolder.clear();
}

JSONObject::JSONObject(std::string str) {
    deleteSpaces(str);

    if(str[0] == '{' && str[str.size()-1] == '}'){
        str.erase(str.size()-1,1);
        str.erase(0,1);
    }
    else{
        printERR("no {}");
    }

    JSONObjectType jsonObjectType;
    jsonObjectType.type = JSON_NULL;
    jsonObjectType.index = 0;

    std::string name{},value{};

    bool isInString = false
            ,needName = true;
    unsigned int in = 0;

    for(unsigned long long i = 0;i < str.size();i++) {
        if(str[i] == '\"' && (i == 0 || str[i-1] != '\\'))
            isInString = !isInString;

        if(isInString)
            goto COLLECT;

        if((str[i] == '[' || str[i] == '{'))
            in++;
        else if((str[i] == ']' || str[i] == '}'))
            in--;
        if((in == 0) && (str[i] == ':')) {
            if(!needName)
                printERR("bad JSON Input \"{" + str + "}\"");
            needName = false;
            value.clear();
            continue;
        }
        else if(((in == 0) && (str[i] == ',')) || i+1 == str.size()){
            if(needName)
                printERR("bad JSON Input \"{" + str + "}\"");
            needName = true;

            if(name[0] != name[name.size()-1] || (name[0] != '\"' && name[0] != '\''))
                printERR("bad name \"" + name + '\"');

            name = name.substr(1,name.size()-2);

            if(i+1 == str.size())
                value += str[i];

            if((value[0] == '\"' && value[value.size()-1] == '\"') || (value[0] == '\'' && value[value.size()-1] == '\'')){
                if(value[value.size()-2] == '\\')
                    printERR("no closing string at " + value);

                jsonObjectType.type = JSON_STRING;
                jsonObjectType.index = stringHolder.size();

                stringHolder.push_back(value.substr(1,value.size()-2));
            }
            else if(isdigit(value[value.size()-1])){
                jsonObjectType.type = JSON_NUMBER;
                jsonObjectType.index = numberHolder.size();

                numberHolder.push_back(std::stold(value));
            }
            else if(value == "true" || value == "false"){
                jsonObjectType.type = JSON_BOOLEAN;
                jsonObjectType.index = boolHolder.size();

                boolHolder.push_back(value == "true");
            }
            else if(value[0] == '['){
                jsonObjectType.type = JSON_ARRAY;
                jsonObjectType.index = jsonArrayHolder.size();

                jsonArrayHolder.emplace_back(value);
            }
            else if(value[0] == '{'){
                jsonObjectType.type = JSON_OBJECT;
                jsonObjectType.index = jsonObjectHolder.size();

                jsonObjectHolder.emplace_back(value);
            }
            else if(value == "null"){
                jsonObjectType.type = JSON_NULL;
            }
            else{
                printERR("unknown value \"" + value + '\"');
            }


            if(isExist(name)){
                printERR(name + " is exist");
            }else{
                typeHolder[name] = jsonObjectType;
            }

            name.clear();
            continue;
        }


        COLLECT:
        if(needName)
            name += str[i];
        else
            value += str[i];
    }
}

JSONObject::~JSONObject() {
    boolHolder.clear();
    numberHolder.clear();
    stringHolder.clear();
    jsonArrayHolder.clear();
    jsonObjectHolder.clear();
    typeHolder.clear();
}

JSONObject::JSONObject(const JSONObject & jsonObject) = default;

JSONObject &JSONObject::operator=(const JSONObject &jsonObject) = default;

//private
void JSONObject::printERR(const std::string &error) {
    std::cerr << "JSONObjectERR: " << error << std::endl;
    exit(-1);
}

std::string JSONObject::toString() const {
    std::string result{'{'};

    for(const auto& i : typeHolder){
        result += '\"' + i.first + "\":";

        switch (i.second.type) {
            case JSON_NULL:
                result += "null";
                break;
            case JSON_BOOLEAN:
                result += boolHolder[i.second.index]? "true" : "false";
                break;
            case JSON_NUMBER:
                result += std::to_string(numberHolder[i.second.index]);
                break;
            case JSON_STRING:
                result += '\"' + stringHolder[i.second.index] + '\"';
                break;
            case JSON_ARRAY:
                result += jsonArrayHolder[i.second.index].toString();
                break;
            case JSON_OBJECT:
                result += jsonObjectHolder[i.second.index].toString();
                break;
            default:
                printERR("unknown type " + std::to_string(i.second.type));
                break;
        }
        result += ',';
    }
    result[result.size()-1] = '}';

    return result;
}

bool JSONObject::isExist(const std::string &name) {
    return typeHolder.find(name) != typeHolder.end();
}