#ifndef JSON_JSONARRAY_HPP
#define JSON_JSONARRAY_HPP

#include "../object/Object.hpp"
#include "../additional/macros.hpp"
#include <vector>
#include <string>

namespace json{
    class Object;
    class JSONArray{
        friend class JSONObject;
    public:
        typedef std::vector<Object>::size_type size_type;
    private:
        std::vector<Object> holder;
    public:
        JSONArray();
        explicit JSONArray(const std::string &str);
    private:
        JSONArray(std::string::const_iterator &begin,std::string::const_iterator end);
    public:
        JSONArray(const JSONArray&) = default;
        JSONArray(JSONArray &&jsonArray) noexcept;

        JSONArray &operator=(const JSONArray&) = default;
        JSONArray &operator=(JSONArray&&);

        Object &operator[](size_type key);
        const Object &operator[](size_type index) const;

        std::string toString() const;

        size_type size() const;

    private:
        void getNextValue(std::string::const_iterator &begin,std::string::const_iterator end);
    };
}//namespace json


#endif//JSON_JSONARRAY_HPP