#include "Translator.h"
#include "gtest/gtest.h"


class TranslatorFixture : public ::testing::Test {

protected:
    void TearDown() override {

    }

    void SetUp() override {

    }

public:
    Translator *t;

    TranslatorFixture() {
        t = new Translator();
    }

    ~TranslatorFixture() override {
        delete t;
    }

};

TEST_F(TranslatorFixture, EnglishToFrench) {
    t->set_lang(English, French);

    ASSERT_EQ("Espace vectoriel", t->translate_wiki("Vector space"));
    ASSERT_EQ("Corps commutatif", t->translate_wiki("Field"));
    ASSERT_EQ("Formule du binôme de Newton", t->translate_wiki("Binomial expansion"));
    ASSERT_EQ("Formule du binôme de Newton", t->translate_wiki("Binomial theorem"));
}

TEST_F(TranslatorFixture, EnglishToVietnamese) {
    t->set_lang(English, Vietnamese);

    ASSERT_EQ("Trường", t->translate_wiki("Field"));
    ASSERT_EQ("Hàm số", t->translate_wiki("Function"));
    ASSERT_EQ("Dãy", t->translate_wiki("Sequence"));
}


TEST_F(TranslatorFixture, FrenchToEnglish) {
    t->set_lang(French, English);

    ASSERT_EQ("Vector space", t->translate_wiki("Espace vectoriel"));
    ASSERT_EQ("Binomial theorem", t->translate_wiki("Formule du binôme de Newton"));
    ASSERT_EQ("Binomial theorem", t->translate_wiki("binome de newton"));

    //ASSERT_EQ("Field", t->translate_wiki("Corps")); //to fix
}

TEST_F(TranslatorFixture, VietnameseToFrench) {
    t->set_lang(Vietnamese, French);

    ASSERT_EQ("Suite", t->translate_wiki("Dãy"));
    // ASSERT_EQ("Suite", t->translate_wiki("Dãy số")); // to fix
    ASSERT_EQ("Corps commutatif", t->translate_wiki("Trường"));
    ASSERT_EQ("Fonction", t->translate_wiki("Hàm số"));
}
