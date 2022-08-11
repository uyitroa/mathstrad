project(tests)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/Cellar/icu4c/70.1/include)
link_directories(/usr/local/Cellar/icu4c/70.1/lib)

find_package(CURL REQUIRED)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(mathstradTest TranslatorTest.cpp)

target_link_libraries(mathstradTest gtest gtest_main)
target_link_libraries(mathstradTest src)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(mathstradTest ${CURL_LIBRARIES})
else(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

target_link_libraries(mathstradTest icuuc)