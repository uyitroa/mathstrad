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


using namespace icu;

typedef std::map<std::string, std::string> Params;

std::string addParameters(const std::string &url, const Params &params);

bool is_substring(const UnicodeString& substring, const std::string& whole_string, int substring_length, UErrorCode &status);

std::string clean_paranthesis(const std::string &word);


#endif //MATHSTRAD_UTILS_H
