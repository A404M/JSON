#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include <string>
#include "../additional/macros.hpp"

namespace json{
    class JSONArray;
    class JSONObject;

    class Object{
    public:
        using Bool = bool;
        using Number = long double;
        using String = std::string;
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
        explicit Object(Bool b);
        explicit Object(Number num);
        explicit Object(const char *str);
        explicit Object(const String &str);
        explicit Object(const JSONArray &jsonArray);
        explicit Object(const JSONObject &jsonObject);
        Object(const Object &object);

        ~Object();

        Object &operator=(std::nullptr_t);
        Object &operator=(Bool b);
        Object &operator=(Number num);
        Object &operator=(const char *str);
        Object &operator=(const String &str);
        Object &operator=(const JSONArray &jsonArray);
        Object &operator=(const JSONObject &jsonObject);
        Object &operator=(const Object &object);

        Type getType() const;

        bool isNull();
        
        Bool& getBool();
        Number& getNumber();
        String& getString();
        JSONArray& getJSONArray();
        JSONObject& getJSONObject();

        const Bool& getBool() const;
        const Number& getNumber() const;
        const String& getString() const;
        const JSONArray& getJSONArray() const;
        const JSONObject& getJSONObject() const;

        std::string toString() const;
    private:
        void delVal();
    };
}//namespace json

#endif//JSON_OBJECT_HPP