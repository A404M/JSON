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
        explicit Object(String &&str);
        explicit Object(JSONArray &&jsonArray);
        explicit Object(JSONObject &&jsonObject);
        Object(const Object &object);
        Object(Object &&object) noexcept;

        ~Object();

        Object &operator=(std::nullptr_t);
        Object &operator=(Bool b);
        Object &operator=(Number num);
        Object &operator=(const char *str);
        Object &operator=(const String &str);
        Object &operator=(const JSONArray &jsonArray);
        Object &operator=(const JSONObject &jsonObject);
        Object &operator=(String &&str);
        Object &operator=(JSONArray &&jsonArray);
        Object &operator=(JSONObject &&jsonObject);
        Object &operator=(const Object &object);
        Object &operator=(Object &&object) noexcept;

        really_inline Type getType() const;

        really_inline bool isNull();

        really_inline Bool& getBool();
        really_inline Number& getNumber();
        really_inline String& getString();
        really_inline JSONArray& getJSONArray();
        really_inline JSONObject& getJSONObject();

        really_inline const Bool& getBool() const;
        really_inline const Number& getNumber() const;
        really_inline const String& getString() const;
        really_inline const JSONArray& getJSONArray() const;
        really_inline const JSONObject& getJSONObject() const;

        std::string toString() const;
    private:
        void delVal();
    };
}//namespace json

#endif//JSON_OBJECT_HPP