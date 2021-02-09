cmake_minimum_required(VERSION 3.17)
project(JSON)

set(CMAKE_CXX_STANDARD 20)

add_executable(JSON main.cpp JSON/JSONObject.cpp JSON/JSONObject.h JSON/JSONArray.cpp JSON/JSONArray.h JSON/functions.h JSON/JSON.h JSON/others.h)