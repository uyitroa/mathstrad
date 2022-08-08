//
// Created by yuitora . on 08/08/2022.
//

#ifndef MATHSTRAD_LANGUAGES_H
#define MATHSTRAD_LANGUAGES_H

#include <map>

enum Language {
    English,
    French,
    Vietnamese,
    Japanese
};

static std::map<Language, std::string> LanguageCode {
        {English, "en"},
        {French, "fr"},

        {Vietnamese, "vi"},
        {Japanese, "ja"},

};

#endif //MATHSTRAD_LANGUAGES_H
