cmake_minimum_required(VERSION 3.23)
project(mathstrad)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

find_package(CURL REQUIRED)

include_directories(/usr/local/Cellar/icu4c/70.1/include)
link_directories(/usr/local/Cellar/icu4c/70.1/lib)

add_executable(mathstrad ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(mathstrad ${CURL_LIBRARIES})
else(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

target_link_libraries(mathstrad icuuc)

target_link_libraries(mathstrad src)
