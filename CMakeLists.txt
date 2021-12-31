cmake_minimum_required(VERSION 3.17)
project(JSON)

set(CMAKE_CXX_COMPILER g++-10)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-Ofast")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

file(GLOB LIB_SOURCES 
				json/additional/*.cpp
				json/json-array/*.cpp
				json/json-object/*.cpp
				json/object/*.cpp)
file(GLOB LIB_HEADERS
				json/additional/*.hpp 
				json/json-array/*.hpp
				json/json-object/*.hpp
				json/object/*.hpp
				json/*.hpp)

set(JSON_LIB ${LIB_SOURCES} ${LIB_HEADERS})

add_executable(JSON main.cpp ${JSON_LIB})

#[[
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")]]