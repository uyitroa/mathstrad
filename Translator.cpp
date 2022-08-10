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


/*
 * Get the right page wiki for the word in the original language, then get the same page wiki in the desired language.
 * Extract the title of that wiki page and return it.
 */
std::string Translator::translate_wiki(const std::string& word) {
    if (!curl) {return "";}

    std::string pageid = this->get_pageid(word);

    // Get wikipage in the desired language with the pageid of the original language.
    std::string readBuffer;

    Params p {{"action", "query"},
             {"format", "json"},
             {"prop", "langlinks"},
             {"pageids", pageid},
             {"lllang", LanguageCode[this->to_lang]},
             {"lllimit", "100"}};


    std::string url = addParameters(this->wiki_url, p);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);

    json data = json::parse(readBuffer);

    return data["query"]["pages"][pageid]["langlinks"][0]["*"];
}

/*
 * Get the right page wiki for the word in the original language.
 * Return pageid.
*/
std::string Translator::get_pageid(const std::string& word) {
    if (!curl) {return "";}

    std::string readBuffer;

    // search for the word + " maths"
    std::string param_word(word);
    param_word.append(" ");
    param_word.append(this->math_word);

    // format string for url request
    param_word.assign(curl_easy_escape(curl, param_word.c_str(), param_word.length()));

    Params p {{"action", "query"},
              {"list", "search"},
              {"format", "json"},
              {"srsearch", param_word},
              {"srwhat", "text"},
              {"srlimit", "100"}};

    std::string url = addParameters(this->wiki_url, p);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);

    json data = json::parse(readBuffer.c_str());

    /*
     * Algorithm to find the right page if word is ambigous
     */
    std::string pageid = this->find_right_pageid(data, word);

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

std::string Translator::find_right_pageid(const json &data, const std::string &word) {

    json results_array = data["query"]["search"];
    int array_size = results_array.size();

    UnicodeString word_uni;
    word_uni.setTo(word.c_str());

    for (int i = 0; i < array_size; i++) {

        std::string wiki_title = to_string(data["query"]["search"][i]["title"]);

        // Check if math_word is in wiki_title using icu compare, for case-insensitive and equivalent stuffs
        for (int j = 0; j < wiki_title.length() - word.length(); j++) {

            UnicodeString part_wiki_title_uni;
            part_wiki_title_uni.setTo(wiki_title.substr(j, word.length()).c_str());

            /*
             * To improve
             */
            if (Normalizer::compare(part_wiki_title_uni, word_uni, U_COMPARE_IGNORE_CASE, status) == 0) {
                return to_string(data["query"]["search"][i]["pageid"]);
            }
        }
    }

    return to_string(data["query"]["search"][1]["pageid"]);
}

void Translator::get_math_word() {

    if (this->from_lang == English) {
        this->math_word.assign("Mathematics");
        this->math_word_uni.setTo(this->math_word.c_str());
        return;}

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
    this->math_word_uni.setTo(this->math_word.c_str());
}

