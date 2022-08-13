//
// Created by yuitora . on 08/08/2022.
//

#include <string>

#include "Translator.h"
#include "utils.h"


Translator::Translator(Language from_lang, Language to_lang) {
    curl = curl_easy_init();
    u_init(&status);
    this->from_lang = from_lang;
    this-> to_lang = to_lang;
    this->init();

}

Translator::Translator() {
    curl = curl_easy_init();
    u_init(&status);
    this->from_lang = English;
    this->to_lang = English;
    this->init();
}

Translator::~Translator() {
    curl_easy_cleanup(this->curl);
    u_cleanup();

}

void Translator::init() {
    this->langCode = LanguageCode[from_lang];
    std::stringstream ss;
    ss << "https://" << this->langCode << ".wikipedia.org/w/api.php";
    this->wiki_url.assign(ss.str());

    this->get_math_word();
}

void Translator::set_lang(Language from_lang, Language to_lang) {
    this->from_lang = from_lang;
    this->to_lang = to_lang;
    this->init();
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

    std::string url = addParameters("https://en.wikipedia.org/w/api.php", p);

    json data = send_get_request(curl, url);

    this->math_word = data["query"]["pages"][MATHS_PAGEID_EN]["langlinks"][0]["*"];
    this->math_word_uni.setTo(this->math_word.c_str());
}

/*
 * Get the right page wiki for the word in the original language, then get the same page wiki in the desired language.
 * Extract the title of that wiki page and return it.
 * bool suggest is to try to translate another word in case the original word can't be translated
 */
std::string Translator::translate_wiki(const std::string& word, bool suggest) {
    if (!curl) {return "";}

    std::string backup_pageid; // in case pageid can't be translated
    std::string pageid = this->get_pageid(word, backup_pageid);

    // Get wikipage in the desired language with the pageid of the original language.

    Params p {{"action", "query"},
             {"format", "json"},
             {"prop", "langlinks"},
             {"pageids", pageid},
             {"lllang", LanguageCode[this->to_lang]},
             {"lllimit", "100"}};


    std::string url = addParameters(this->wiki_url, p);

    json data = send_get_request(curl, url);

    std::string translated_title;
    try {
        translated_title = data["query"]["pages"][pageid]["langlinks"][0]["*"];
    } catch (const nlohmann::detail::type_error &exc) {
        std::cerr << exc.what() << " in translated_title = data in translate_wiki()" << std::endl;
        if (!suggest) {return "";}

        p["pageids"] = backup_pageid;
        url.assign(addParameters(this->wiki_url, p));
        json data1 = send_get_request(curl, url);

        try {
            translated_title = data1["query"]["pages"][backup_pageid]["langlinks"][0]["*"];
        } catch (const nlohmann::detail::type_error &exc) {
            std::cerr << exc.what() << " in translated_title = data1 in translate_wiki()" <<std::endl;
            translated_title = "";
        }
    }
    std::string translated_word = clean_paranthesis(translated_title);
    return translated_word;
}

/*
 * Get the right page wiki for the word in the original language.
 * std::string &suggestion is to suggest other word in case the searched word can't be translated.
 * Return pageid.
*/
std::string Translator::get_pageid(const std::string& word, std::string &suggestion) {
    if (!curl) {return "";}

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

    json data = send_get_request(curl, url);

    /*
     * Algorithm to find the right page if word is ambigous
     */
    // TODO: improve this shit
    std::string pageid = this->find_right_pageid(data, word, suggestion);

    return pageid;
}

/*
 * without std::string &suggestion
 */
std::string Translator::get_pageid(const std::string &word) {
    std::string _;
    return get_pageid(word, _);
}

/*
 * std::string &suggestion is to suggest other word in case the searched word can't be translated.
 */
std::string Translator::find_right_pageid(const json &data, const std::string &word, std::string &suggestion) {

    json results_array = data["query"]["search"];
    int array_size = results_array.size();

    UnicodeString word_uni;
    word_uni.setTo(word.c_str());

    for (int i = 0; i < array_size; i++) {

        std::string wiki_title = to_string(data["query"]["search"][i]["title"]);

        // Check if math_word is in wiki_title using icu compare, for case-insensitive and equivalent stuffs
        // TODO: improve algorithm of finding the right word
        if (is_substring(word_uni, wiki_title, word.length(), status)) {

            try {
                if (i == 0) {suggestion.assign(to_string(data["query"]["search"][1]["pageid"]));}
                else {suggestion.assign(to_string(data["query"]["search"][0]["pageid"]));}

            } catch (const nlohmann::detail::type_error &exc) {
                suggestion.assign("");
            }

            return to_string(data["query"]["search"][i]["pageid"]);
        }
    }

    try {
        suggestion.assign(to_string(data["query"]["search"][1]["pageid"]));
    } catch (const nlohmann::detail::type_error &exc) {
        suggestion.assign("");
    }

    return to_string(data["query"]["search"][0]["pageid"]);
}

/*
 * without std:;string &suggestion
 */
std::string Translator::find_right_pageid(const json &data, const std::string &word) {
    std::string _;
    return this->find_right_pageid(data, word, _);
}

std::string Translator::translate(const std::string &word) {
    std::string wiki_res = this->translate_wiki(word, true);
    if (!wiki_res.empty()) {return wiki_res;}

    /*
     * TODO: add other translation algorithm if wiki doesn't work
     */

    return "";
}

