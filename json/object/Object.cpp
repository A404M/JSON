#include "Object.hpp"
#include "../json-array/JSONArray.hpp"
#include "../json-object/JSONObject.hpp"
#include <sstream>
#include <iomanip>

using namespace json;

Object::Object(nullptr_t): holder(nullptr), type(NULL_T){
    //empty
}
Object::Object(bool b): holder(new bool(b)), type(BOOL_T){
    //empty
}
Object::Object(long double num): holder(new long double(num)), type(DOUBLE_T){
    //empty
}
Object::Object(const char *str): holder(new std::string(str)), type(STRING_T){
    //empty
}
Object::Object(const std::string &str): holder(new std::string(str)), type(STRING_T){
    //empty
}
Object::Object(const JSONArray &jsonArray): holder(new JSONArray(jsonArray)), type(JSON_ARRAY_T){
    //empty
}
Object::Object(const JSONObject &jsonObject): holder(new JSONObject(jsonObject)), type(JSON_OBJECT_T){
    //empty
}
extern int c;
Object::Object(const Object &object): type(object.type){
    c++;
    switch (type) {
        case NULL_T:
            break;
        case BOOL_T:
            holder = new bool(*((bool *) object.holder));
            break;
        case DOUBLE_T:
            holder = new long double(*((long double *) object.holder));
            break;
        case STRING_T:
            holder = new std::string(*((std::string *) object.holder));
            break;
        case JSON_ARRAY_T:
            holder = new JSONArray(*((JSONArray *) object.holder));
            break;
        case JSON_OBJECT_T:
            holder = new JSONObject(*((JSONObject *) object.holder));
            break;
        default:
            throw std::runtime_error("Object::Object");
    }
}

Object::~Object(){
    delVal();
}

Object &Object::operator=(std::nullptr_t){
    if(type != NULL_T) {
        delVal();
        type = NULL_T;
    }
    return *this;
}
Object &Object::operator=(bool b){
    if(type == BOOL_T){
        *(bool*)holder = b;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = BOOL_T;
        holder = new bool(b);
    }
    return *this;
}
Object &Object::operator=(long double num){
    if(type == DOUBLE_T){
        *(long double*)holder = num;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = DOUBLE_T;
        holder = new long double(num);
    }
    return *this;
}
Object &Object::operator=(const char *str){
    if(type == STRING_T){
        *(std::string*)holder = str;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = STRING_T;
        holder = new std::string(str);
    }
    return *this;
}
Object &Object::operator=(const std::string &str){
    if(type == STRING_T){
        *(std::string*)holder = str;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = STRING_T;
        holder = new std::string(str);
    }
    return *this;
}
Object &Object::operator=(const JSONArray &jsonArray){
    if(type == JSON_ARRAY_T){
        *(JSONArray*)holder = jsonArray;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = JSON_ARRAY_T;
        holder = new JSONArray(jsonArray);
    }
    return *this;
}
Object &Object::operator=(const JSONObject &jsonObject){
    if(type == JSON_OBJECT_T){
        *(JSONObject*)holder = jsonObject;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = JSON_OBJECT_T;
        holder = new JSONObject(jsonObject);
    }
    return *this;
}
Object &Object::operator=(const Object &object){
    if(type == object.type){
        switch (type) {
            case NULL_T:
                break;
            case BOOL_T:
                *((bool *)holder) = *((bool*)object.holder);
                break;
            case DOUBLE_T:
                *((long double *)holder) = *((long double*)object.holder);
                break;
            case STRING_T:
                *((std::string *)holder) = *((std::string*)object.holder);
                break;
            case JSON_ARRAY_T:
                *((JSONArray *)holder) = *((JSONArray*)object.holder);
                break;
            case JSON_OBJECT_T:
                *((JSONObject *)holder) = *((JSONObject*)object.holder);
                break;
            default:
                throw std::runtime_error("Object::delVal");
        }
    }else{
        delVal();
        type = object.type;
        switch (type) {
            case NULL_T:
                break;
            case BOOL_T:
                holder = new bool(*((bool *) object.holder));
                break;
            case DOUBLE_T:
                holder = new long double(*((long double *) object.holder));
                break;
            case STRING_T:
                holder = new std::string(*((std::string *) object.holder));
                break;
            case JSON_ARRAY_T:
                holder = new JSONArray(*((JSONArray *) object.holder));
                break;
            case JSON_OBJECT_T:
                holder = new JSONObject(*((JSONObject *) object.holder));
                break;
            default:
                throw std::runtime_error("Object::delVal");
        }
    }
    return *this;
}

Object::Type Object::getType() const{
    return type;
}

bool Object::isNull(){
    return type == NULL_T;
}
bool& Object::getBool(){
    return *((bool*)holder);
}
long double& Object::getNumber(){
    return *((long double*)holder);
}
std::string& Object::getString(){
    return *((std::string*)holder);
}
JSONArray& Object::getJSONArray(){
    return *((JSONArray*)holder);
}
JSONObject& Object::getJSONObject(){
    return *((JSONObject*)holder);
}

const bool& Object::getBool() const{
    return *((bool*)holder);
}
const long double& Object::getNumber() const{
    return *((long double*)holder);
}
const std::string& Object::getString() const{
    return *((std::string*)holder);
}
const JSONArray& Object::getJSONArray() const{
    return *((JSONArray*)holder);
}
const JSONObject& Object::getJSONObject() const{
    return *((JSONObject*)holder);
}

std::string Object::toString() const{
    switch (type){
        case NULL_T:
            return "null";
        case BOOL_T:
            return *((bool*)holder)?"true":"false";
        case DOUBLE_T:{
            std::stringstream ss;
            ss << std::setprecision(18) << *((long double*)holder);
            return ss.str();
        }
        case STRING_T:
            return "\"" + *((std::string*)holder) + "\"";
        case JSON_ARRAY_T:
            return ((JSONArray*)holder)->toString();
        case JSON_OBJECT_T:
            return ((JSONObject*)holder)->toString();
        default:
            throw std::runtime_error("Object::delVal");
    }
}

void Object::delVal(){
    switch (type){
    case NULL_T:
        break;
    case BOOL_T:
        delete ((bool*)holder);
        break;
    case DOUBLE_T:
        delete ((long double*)holder);
        break;
    case STRING_T:
        delete ((std::string*)holder);
        break;
    case JSON_ARRAY_T:
        delete ((JSONArray*)holder);
        break;
    case JSON_OBJECT_T:
        delete ((JSONObject*)holder);
        break;
    default:
        throw std::runtime_error("Object::delVal");
    }
}
