#include <iostream>
#include "src/Translator.h"

int main() {

    Translator t(English, French);
    std::cout << t.translate_wiki("Field") << std::endl;
    return 0;
}
