//
// Created by yuitora . on 08/08/2022.
//

#ifndef MATHSTRAD_TRANSLATOR_H
#define MATHSTRAD_TRANSLATOR_H


#include <iostream>
#include <curl/curl.h>
#include "Languages.h"
#include "jsonparser/json.h"

using json = nlohmann::json;

class Translator {
private:
    Language from_lang, to_lang;
    std::string langCode;
    std::string wiki_url;

    const std::string MATHS_PAGEID_EN = "18831";

    CURL *curl;

    void init();

    std::string get_pageid(const std::string& word);

    std::string find_right_pageid(const json &data);

    void get_math_word();

    std::string math_word;

public:
    Translator(Language from_lang, Language to_lang);
    Translator();

    ~Translator();

    std::string translate_wiki(const std::string& word);

};


#endif //MATHSTRAD_TRANSLATOR_H
