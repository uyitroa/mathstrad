project(src)

set(HEADER_FILES
        Languages.h
        Translator.h
        utils.h)

set(SOURCE_FILES
        Translator.cpp
        utils.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})