#include <iostream>
#include "Translator.h"

int main() {

    Translator t(French, English);
    std::cout << t.translate_wiki("Corps") << std::endl;
    return 0;
}
