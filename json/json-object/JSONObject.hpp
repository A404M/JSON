#ifndef JSON_JSONOBJECT_HPP
#define JSON_JSONOBJECT_HPP

#include "../additional/macros.hpp"
#include <string>
#include <unordered_map>
#include "../object/Object.hpp"

namespace json{
    class Object;
    class JSONObject{
        friend class JSONArray;
    public:
        using size_type = std::unordered_map<std::string,Object>::size_type;
    private:
        std::unordered_map<std::string,Object> holder;
    public:
        JSONObject();
        explicit JSONObject(const std::string &str);
    private:
        JSONObject(std::string::const_iterator &begin,std::string::const_iterator end);
    public:
        JSONObject(const JSONObject&) = default;
        JSONObject(JSONObject &&jsonObject) noexcept;

        JSONObject &operator=(const JSONObject&) = default;
        JSONObject &operator=(JSONObject &&jsonObject) noexcept;

        Object &operator[](const std::string &key);
        const Object &operator[](const std::string &key) const;

        std::string toString() const;

        size_type size() const;

    private:
        void getNextValue(std::string::const_iterator &begin,std::string::const_iterator end);
    };
}//namespace json


#endif//JSON_JSONOBJECT_HPP