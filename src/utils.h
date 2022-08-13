//
// Created by yuitora . on 08/08/2022.
//

#ifndef MATHSTRAD_UTILS_H
#define MATHSTRAD_UTILS_H

#include <iostream>
#include <sstream>
#include <map>
#include <unicode/utypes.h>
#include <unicode/uclean.h>
#include <unicode/unistr.h>
#include <unicode/normlzr.h>
#include <unicode/uchar.h>
#include <curl/curl.h>
#include "jsonparser/json.h"


using namespace icu;
using json = nlohmann::json;

typedef std::map<std::string, std::string> Params;

std::string addParameters(const std::string &url, const Params &params);

bool is_substring(const UnicodeString& substring, const std::string& whole_string, int substring_length, UErrorCode &status);

std::string clean_paranthesis(const std::string &word);

json send_get_request(CURL *curl, const std::string &url);

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


#endif //MATHSTRAD_UTILS_H
