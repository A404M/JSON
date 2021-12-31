#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include <string>
#include "../additional/macros.hpp"

namespace json{
    class JSONArray;
    class JSONObject;

    class Object{
    public:
        enum Type{
            NULL_T,
            BOOL_T,
            DOUBLE_T,
            STRING_T,
            JSON_ARRAY_T,
            JSON_OBJECT_T
        };
    private:
        void*__restrict holder;
        Type type = NULL_T;
    public:
        explicit Object(nullptr_t = nullptr);//null
        explicit Object(bool b);
        explicit Object(long double num);
        explicit Object(const char *str);
        explicit Object(const std::string &str);
        explicit Object(const JSONArray &jsonArray);
        explicit Object(const JSONObject &jsonObject);
        Object(const Object &object);

        ~Object();

        Object &operator=(std::nullptr_t);
        Object &operator=(bool b);
        Object &operator=(long double num);
        Object &operator=(const char *str);
        Object &operator=(const std::string &str);
        Object &operator=(const JSONArray &jsonArray);
        Object &operator=(const JSONObject &jsonObject);
        Object &operator=(const Object &object);

        Type getType() const;

        bool isNull();
        
        bool& getBool();
        long double& getNumber();
        std::string& getString();
        JSONArray& getJSONArray();
        JSONObject& getJSONObject();

        const bool& getBool() const;
        const long double& getNumber() const;
        const std::string& getString() const;
        const JSONArray& getJSONArray() const;
        const JSONObject& getJSONObject() const;

        std::string toString() const;
    private:
        really_inline void delVal();
    };
}//namespace json

#endif//JSON_OBJECT_HPP