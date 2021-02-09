//
// Created by a404m on 2/5/21.
//

#ifndef JSON_JSONARRAY_H
#define JSON_JSONARRAY_H

#include <vector>
#include <string>
#include "others.h"

struct JSONArrayType{
    TheJSONType type = JSON_NULL;
    unsigned long long index = 0;
};

class JSONArray {
private:
    std::vector<std::string> stringHolder{};
    std::vector<bool> boolHolder{};
    std::vector<long double> numberHolder{};
    std::vector<JSONArray> jsonArrayHolder{};
    std::vector<JSONObject> jsonObjectHolder{};
    std::vector<JSONArrayType> typeHolder{};
public:
    JSONArray();
    explicit JSONArray(std::string);
    JSONArray(const JSONArray&);
    ~JSONArray();

    JSONArray& operator=(const JSONArray&);
    TheJSONType getTypeAt(const unsigned long long&);
    bool getBoolAt(const unsigned long long&);
    long double getNumberAt(const unsigned long long&);
    std::string getStringAt(const unsigned long long&);
    JSONArray getJSONArrayAt(const unsigned long long&);

    std::string toString() const;

private:
    static void printERR(const std::string&);
};


#endif //JSON_JSONARRAY_H
