#include "Object.hpp"
#include "../json-array/JSONArray.hpp"
#include "../json-object/JSONObject.hpp"
#include <sstream>
#include <iomanip>

using namespace json;

using Bool = Object::Bool;
using Number = Object::Number;
using String = Object::String;

Object::Object(nullptr_t): holder(nullptr), type(NULL_T){/*empty*/}
Object::Object(Bool b): holder(new Bool(b)), type(BOOL_T){/*empty*/}
Object::Object(Number num): holder(new Number(num)), type(DOUBLE_T){/*empty*/}
Object::Object(const char *str): holder(new String(str)), type(STRING_T){/*empty*/}
Object::Object(const String &str): holder(new String(str)), type(STRING_T){/*empty*/}
Object::Object(const JSONArray &jsonArray): holder(new JSONArray(jsonArray)), type(JSON_ARRAY_T){/*empty*/}
Object::Object(const JSONObject &jsonObject): holder(new JSONObject(jsonObject)), type(JSON_OBJECT_T){/*empty*/}
Object::Object(String &&str): holder(new String(std::move(str))), type(STRING_T){/*empty*/}
Object::Object(JSONArray &&jsonArray): holder(new JSONArray(std::move(jsonArray))), type(JSON_ARRAY_T){/*empty*/}
Object::Object(JSONObject &&jsonObject): holder(new JSONObject(std::move(jsonObject))), type(JSON_OBJECT_T){/*empty*/}
Object::Object(const Object &object): type(object.type){
    switch (type) {
        case NULL_T:
            break;
        case BOOL_T:
            holder = new Bool(*reinterpret_cast<Bool*>(object.holder));
            break;
        case DOUBLE_T:
            holder = new Number(*reinterpret_cast<Number*>(object.holder));
            break;
        case STRING_T:
            holder = new String(*reinterpret_cast<String*>(object.holder));
            break;
        case JSON_ARRAY_T:
            holder = new JSONArray(*reinterpret_cast<JSONArray*>(object.holder));
            break;
        case JSON_OBJECT_T:
            holder = new JSONObject(*reinterpret_cast<JSONObject*>(object.holder));
            break;
        default:
            throw std::runtime_error("Object::Object");
    }
}
Object::Object(Object &&object)  noexcept : holder(object.holder), type(object.type){
    object.type = NULL_T;
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
Object &Object::operator=(Bool b){
    if(type == BOOL_T){
        *reinterpret_cast<Bool*>(holder) = b;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = BOOL_T;
        holder = new Bool(b);
    }
    return *this;
}
Object &Object::operator=(Number num){
    if(type == DOUBLE_T){
        *reinterpret_cast<Number*>(holder) = num;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = DOUBLE_T;
        holder = new Number(num);
    }
    return *this;
}
Object &Object::operator=(const char *str){
    if(type == STRING_T){
        *reinterpret_cast<String*>(holder) = str;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = STRING_T;
        holder = new String(str);
    }
    return *this;
}
Object &Object::operator=(const String &str){
    if(type == STRING_T){
        *reinterpret_cast<String*>(holder) = str;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = STRING_T;
        holder = new String(str);
    }
    return *this;
}
Object &Object::operator=(const JSONArray &jsonArray){
    if(type == JSON_ARRAY_T){
        *reinterpret_cast<JSONArray*>(holder) = jsonArray;
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
        *reinterpret_cast<JSONObject*>(holder) = jsonObject;
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = JSON_OBJECT_T;
        holder = new JSONObject(jsonObject);
    }
    return *this;
}
Object &Object::operator=(String &&str){
    if(type == STRING_T){
        *reinterpret_cast<String*>(holder) = std::move(str);
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = STRING_T;
        holder = new String(std::move(str));
    }
    return *this;
}
Object &Object::operator=(JSONArray &&jsonArray){
    if(type == JSON_ARRAY_T){
        *reinterpret_cast<JSONArray*>(holder) = std::move(jsonArray);
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = JSON_ARRAY_T;
        holder = new JSONArray(std::move(jsonArray));
    }
    return *this;
}
Object &Object::operator=(JSONObject &&jsonObject){
    if(type == JSON_OBJECT_T){
        *reinterpret_cast<JSONObject*>(holder) = std::move(jsonObject);
    }else{
        if (type != NULL_T) {
            delVal();
        }
        type = JSON_OBJECT_T;
        holder = new JSONObject(std::move(jsonObject));
    }
    return *this;
}
Object &Object::operator=(const Object &object){
    if(type == object.type){
        switch (type) {
            case NULL_T:
                break;
            case BOOL_T:
                *reinterpret_cast<Bool*>(holder) = *reinterpret_cast<Bool*>(object.holder);
                break;
            case DOUBLE_T:
                *reinterpret_cast<Number*>(holder) = *reinterpret_cast<Number*>(object.holder);
                break;
            case STRING_T:
                *reinterpret_cast<String*>(holder) = *reinterpret_cast<String*>(object.holder);
                break;
            case JSON_ARRAY_T:
                *reinterpret_cast<JSONArray*>(holder) = *reinterpret_cast<JSONArray*>(object.holder);
                break;
            case JSON_OBJECT_T:
                *reinterpret_cast<JSONObject*>(holder) = *reinterpret_cast<JSONObject*>(object.holder);
                break;
            default:
                throw std::runtime_error("Object::operator=");
        }
    }else{
        delVal();
        type = object.type;
        switch (type) {
            case NULL_T:
                break;
            case BOOL_T:
                holder = new Bool(*reinterpret_cast<Bool*>(object.holder));
                break;
            case DOUBLE_T:
                holder = new Number(*reinterpret_cast<Number*>(object.holder));
                break;
            case STRING_T:
                holder = new String(*reinterpret_cast<String*>(object.holder));
                break;
            case JSON_ARRAY_T:
                holder = new JSONArray(*reinterpret_cast<JSONArray*>(object.holder));
                break;
            case JSON_OBJECT_T:
                holder = new JSONObject(*reinterpret_cast<JSONObject*>(object.holder));
                break;
            default:
                throw std::runtime_error("Object::operator=");
        }
    }
    return *this;
}
Object &Object::operator=(Object &&object) noexcept {
    if(type != NULL_T){
        delVal();
    }
    holder = object.holder;
    type = object.type;
    object.type = NULL_T;
    return *this;
}

Object::Type Object::getType() const{
    return type;
}

bool Object::isNull(){
    return type == NULL_T;
}
Bool& Object::getBool(){
    return *reinterpret_cast<Bool*>(holder);
}
Number& Object::getNumber(){
    return *reinterpret_cast<Number*>(holder);
}
String& Object::getString(){
    return *reinterpret_cast<String*>(holder);
}
JSONArray& Object::getJSONArray(){
    return *reinterpret_cast<JSONArray*>(holder);
}
JSONObject& Object::getJSONObject(){
    return *reinterpret_cast<JSONObject*>(holder);
}

const Bool& Object::getBool() const{
    return *reinterpret_cast<Bool*>(holder);
}
const Number& Object::getNumber() const{
    return *reinterpret_cast<Number*>(holder);
}
const String& Object::getString() const{
    return *reinterpret_cast<String*>(holder);
}
const JSONArray& Object::getJSONArray() const{
    return *reinterpret_cast<JSONArray*>(holder);
}
const JSONObject& Object::getJSONObject() const{
    return *reinterpret_cast<JSONObject*>(holder);
}

std::string Object::toString() const{
    switch (type){
        case NULL_T:
            return "null";
        case BOOL_T:
            return *reinterpret_cast<Bool*>(holder)?"true":"false";
        case DOUBLE_T:{
            std::stringstream ss;
            ss << std::setprecision(18) << *reinterpret_cast<Number*>(holder);
            return ss.str();
        }
        case STRING_T:
            return "\"" + *reinterpret_cast<String*>(holder) + "\"";
        case JSON_ARRAY_T:
            return reinterpret_cast<JSONArray*>(holder)->toString();
        case JSON_OBJECT_T:
            return reinterpret_cast<JSONObject*>(holder)->toString();
        default:
            throw std::runtime_error("Object::delVal");
    }
}

void Object::delVal(){
    switch (type){
    case NULL_T:
        break;
    case BOOL_T:
        delete reinterpret_cast<Bool*>(holder);
        break;
    case DOUBLE_T:
        delete reinterpret_cast<Number*>(holder);
        break;
    case STRING_T:
        delete reinterpret_cast<String*>(holder);
        break;
    case JSON_ARRAY_T:
        delete reinterpret_cast<JSONArray*>(holder);
        break;
    case JSON_OBJECT_T:
        delete reinterpret_cast<JSONObject*>(holder);
        break;
    default:
        throw std::runtime_error("Object::delVal");
    }
}
