//
// Created by yuitora . on 08/08/2022.
//

#ifndef MATHSTRAD_UTILS_H
#define MATHSTRAD_UTILS_H

#include <iostream>
#include <sstream>
#include <map>

typedef std::map<std::string, std::string> Params;

std::string addParameters(const std::string &url, const Params &params);

#endif //MATHSTRAD_UTILS_H
