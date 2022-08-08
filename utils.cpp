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
