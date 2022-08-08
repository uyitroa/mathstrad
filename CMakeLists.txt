cmake_minimum_required(VERSION 3.23)
project(mathstrad)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)

add_executable(mathstrad main.cpp Translator.cpp Translator.h Languages.h utils.cpp utils.h)


if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(mathstrad ${CURL_LIBRARIES})
else(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)
