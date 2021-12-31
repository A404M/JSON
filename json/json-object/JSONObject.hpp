#ifndef JSON_JSONOBJECT_HPP
#define JSON_JSONOBJECT_HPP

#include "../additional/macros.hpp"
#include <string>
#include <map>

namespace json{
    class Object;
    class JSONObject{
    public:
        typedef std::map<std::string,Object>::size_type size_type;
    private:
        std::map<std::string,Object> holder;
    public:
        JSONObject();
        explicit JSONObject(const std::string &str);
        JSONObject(std::string::const_iterator &begin,std::string::const_iterator end);
        JSONObject(const JSONObject&) = default;

        JSONObject &operator=(const JSONObject&) = default;

        Object &operator[](const std::string &key);
        const Object &operator[](const std::string &key) const;

        std::string toString() const;

        size_type size() const;

    private:
        void getNextValue(std::string::const_iterator &begin,std::string::const_iterator end);
    };
}//namespace json


#endif//JSON_JSONOBJECT_HPP