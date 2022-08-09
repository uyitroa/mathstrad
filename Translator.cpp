//
// Created by yuitora . on 08/08/2022.
//

#include <string>

#include "Translator.h"
#include "utils.h"

Translator::Translator(Language from_lang, Language to_lang) {
    curl = curl_easy_init();
    this->from_lang = from_lang;
    this-> to_lang = to_lang;
    this->init();
}

Translator::Translator() {
    curl = curl_easy_init();
    this->from_lang = English;
    this->to_lang = English;
    this->init();
}

Translator::~Translator() {
    curl_easy_cleanup(this->curl);
    u_cleanup();

}

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



std::string Translator::translate_wiki(const std::string& word) {
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

std::string Translator::get_pageid(const std::string& word) {
    if (!curl) {return "";}

    std::string readBuffer;

    std::string param_word("inline:");
    param_word.append(word);

    Params p {{"action", "query"},
              {"list", "search"},
              {"format", "json"},
              {"srsearch", param_word},
              {"srwhat", "text"},
              {"srlimit", "100"}};

    std::string url = addParameters(this->wiki_url, p);
    std::cout << url << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);

    json data = json::parse(readBuffer.c_str());

    std::string pageid = this->find_right_pageid(data);

    return pageid;
}

void Translator::init() {
    u_init(&status);
    this->langCode = LanguageCode[from_lang];
    std::stringstream ss;
    ss << "https://" << this->langCode << ".wikipedia.org/w/api.php";
    this->wiki_url.assign(ss.str());

    this->get_math_word();
}

std::string Translator::find_right_pageid(const json &data) {

//    json results_array = data["query"]["search"];
//    int array_size = results_array.size();
//
//    for (int i = 0; i < array_size; i++) {
//
//    }

    return to_string(data["query"]["search"][2]["pageid"]);
}

void Translator::get_math_word() {

    if (this->from_lang == English) {this->math_word.assign("Mathematics");}

    Params p {{"action", "query"},
              {"format", "json"},
              {"prop", "langlinks"},
              {"pageids", MATHS_PAGEID_EN},
              {"lllang", LanguageCode[this->from_lang]},
              {"lllimit", "100"}};

    std::string readBuffer;
    std::string url = addParameters("https://en.wikipedia.org/w/api.php", p);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);



    json data = json::parse(readBuffer.c_str());

    this->math_word = data["query"]["pages"][MATHS_PAGEID_EN]["langlinks"][0]["*"];

    UnicodeString math_word_uni;
    math_word_uni.setTo(math_word.c_str());

    UnicodeString test;
    test.setTo("toÁN hỌc");

    if (Normalizer::compare(math_word_uni, test, U_COMPARE_IGNORE_CASE, status) == 0) {
        std::cout << "nice" << std::endl;
    }
}

