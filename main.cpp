#include <iostream>
#include "Translator.h"

int main() {

    Translator t(English, Vietnamese);
    std::cout << t.translate_wiki("Integral") << std::endl;
    return 0;
}
