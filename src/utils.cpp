//
// Created by yuitora . on 08/08/2022.
//
#include "utils.h"

std::string addParameters(const std::string &url, const Params &params) {
    std::string new_url(url);
    new_url.append("?");

    for (auto const &x : params) {
        std::stringstream ss;
        ss << x.first << "=" << x.second << "&";
        new_url.append(ss.str());
    }
    return new_url;
}

bool is_substring(const UnicodeString &substring_uni, const std::string &whole_string, int substring_length, UErrorCode &status) {
    if (whole_string.length() < substring_length) {return false;}

    for (int j = 0; j < whole_string.length() - substring_length; j++) {

        UnicodeString part_wholestring_uni;
        part_wholestring_uni.setTo(whole_string.substr(j, substring_length).c_str());

        if (Normalizer::compare(part_wholestring_uni, substring_uni, U_COMPARE_IGNORE_CASE, status) == 0) {
            return true;
        }
    }
    return false;
}

std::string clean_paranthesis(const std::string &word) {
    if (word.at(word.length() - 1) != ')') {return word;}

    std::stringstream ss;

    for (char i : word) {
        if (i == '(') {break;}
        ss << i;
    }
    std::string new_word = ss.str();

    if (new_word.at(new_word.length() - 1) == ' ') {return new_word.substr(0, new_word.length()-1);}
    return new_word;
}

json send_get_request(CURL *curl, const std::string &url) {
    std::string read_buffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

    curl_easy_perform(curl);

    return json::parse(read_buffer);
}
