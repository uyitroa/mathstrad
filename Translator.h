//
// Created by yuitora . on 08/08/2022.
//

#ifndef MATHSTRAD_TRANSLATOR_H
#define MATHSTRAD_TRANSLATOR_H


#include <iostream>
#include <curl/curl.h>
#include "Languages.h"

class Translator {
private:
    Language from_lang, to_lang;
    std::string langCode;
    std::string wiki_url;

    CURL *curl;

    void init();

public:
    Translator(Language from_lang, Language to_lang);
    Translator();

    ~Translator();

    std::string get_pageid(std::string word);

    std::string translate_wiki(std::string word);

};


#endif //MATHSTRAD_TRANSLATOR_H
