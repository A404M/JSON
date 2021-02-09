//
// Created by a404m on 2/5/21.
//

#ifndef JSON_JSONOBJECT_H
#define JSON_JSONOBJECT_H

#include <vector>
#include <map>
#include <string>
#include "others.h"

struct JSONObjectType{
    TheJSONType type = JSON_NULL;
    unsigned long long index = 0;
};

class JSONObject {
private:
    std::vector<std::string> stringHolder{};
    std::vector<bool> boolHolder{};
    std::vector<long double> numberHolder{};
    std::vector<JSONArray> jsonArrayHolder{};
    std::vector<JSONObject> jsonObjectHolder{};
    std::map<std::string,JSONObjectType> typeHolder{};
public:
    JSONObject();
    explicit JSONObject(std::string);
    JSONObject(const JSONObject&);
    ~JSONObject();

    JSONObject& operator=(const JSONObject&);
    TheJSONType getTypeAt(const unsigned long long&);
    bool getBoolAt(const unsigned long long&);
    long double getNumberAt(const unsigned long long&);
    std::string getStringAt(const unsigned long long&);
    JSONObject getJSONObjectAt(const unsigned long long&);

    std::string toString() const;

    bool isExist(const std::string&);

private:
    static void printERR(const std::string&);
};


#endif //JSON_JSONOBJECT_H
