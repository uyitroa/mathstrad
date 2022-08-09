cmake_minimum_required(VERSION 3.23)
project(mathstrad)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(mathstrad main.cpp Translator.cpp Translator.h Languages.h utils.cpp utils.h jsonparser/json.h)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(mathstrad ${Boost_LIBRARIES})
else(Boost_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the Boost library and development files.")
endif(Boost_FOUND)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(mathstrad ${CURL_LIBRARIES})
else(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)
