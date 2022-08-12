#include <iostream>
#include "src/Translator.h"

int main() {

    Translator t(French, English);
    std::cout << t.translate_wiki("corps commutatif") << std::endl;
    return 0;
}
