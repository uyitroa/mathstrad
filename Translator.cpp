//
// Created by yuitora . on 08/08/2022.
//

#include "Translator.h"
#include "utils.h"

Translator::Translator(Language from_lang, Language to_lang) {
    this->from_lang = from_lang;
    this-> to_lang = to_lang;
    this->init();
}

Translator::Translator() {
    this->from_lang = English;
    this->to_lang = English;
    this->init();
}

Translator::~Translator() {
    curl_easy_cleanup(this->curl);

}

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



std::string Translator::translate_wiki(std::string word) {
    if (!curl) {return "";}

    std::string pageid = this->get_pageid(word);

    std::string readBuffer;

    Params p {{"action", "query"},
             {"format", "json"},
             {"prop", "langlinks"},
             {"pageids", pageid},
             {"lllang", LanguageCode[this->to_lang]},
             {"lllimit", "100"}};


    std::string url = addParameters(this->wiki_url, p);
    std::cout << url << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);

    return readBuffer;
}

std::string Translator::get_pageid(std::string word) {
    if (!curl) {return "";}

    std::string readBuffer;

    std::string param_word("inline:");
    param_word.append(word);

    Params p {{"action", "query"},
              {"list", "search"},
              {"format", "json"},
              {"srsearch", param_word},
              {"srwhat", "text"},
              {"srlimit", "20"}};

    std::string url = addParameters(this->wiki_url, p);
    std::cout << url << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);

    return readBuffer;
}

void Translator::init() {
    curl = curl_easy_init();
    this->langCode = LanguageCode[from_lang];
    std::stringstream ss;
    ss << "https://" << this->langCode << ".wikipedia.org/w/api.php";
    this->wiki_url.assign(ss.str());
}

