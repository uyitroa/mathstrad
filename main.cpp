#include <iostream>
#include "Translator.h"

int main() {

    Translator t(Vietnamese, English);
    std::cout << t.translate_wiki("Trường") << std::endl;
    return 0;
}
