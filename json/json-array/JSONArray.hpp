#ifndef JSON_JSONARRAY_HPP
#define JSON_JSONARRAY_HPP

#include "../additional/functions.hpp"
#include <vector>
//#include <string>

namespace json{
    class Object;
    class JSONArray{
    public:
        typedef std::vector<Object>::size_type size_type;
    private:
        std::vector<Object> holder;
    public:
        JSONArray();
        explicit JSONArray(const std::string &str);
        JSONArray(std::string::const_iterator &begin,std::string::const_iterator end);
        JSONArray(const JSONArray&) = default;

        JSONArray &operator=(const JSONArray&) = default;

        Object &operator[](size_type key);
        const Object &operator[](size_type index) const;

        std::string toString() const;

        size_type size() const;

    private:
        really_inline void getNextValue(std::string::const_iterator &begin,std::string::const_iterator end);
    };
}//namespace json


#endif//JSON_JSONARRAY_HPP