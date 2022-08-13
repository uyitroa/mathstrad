#include <iostream>
#include "src/Translator.h"

int main() {

    Translator t(Vietnamese, English);
    std::cout << t.translate("dãy số") << std::endl;
    return 0;
}
