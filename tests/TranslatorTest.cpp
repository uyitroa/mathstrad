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

TEST_F(TranslatorFixture, EnglishToFrenchWiki) {
    t->set_lang(English, French);

    ASSERT_EQ("Espace vectoriel", t->translate_wiki("Vector space", true));
    ASSERT_EQ("Corps commutatif", t->translate_wiki("Field", true));
    ASSERT_EQ("Formule du binôme de Newton", t->translate_wiki("Binomial expansion", true));
    ASSERT_EQ("Formule du binôme de Newton", t->translate_wiki("Binomial theorem", true));
}

TEST_F(TranslatorFixture, EnglishToVietnameseWiki) {
    t->set_lang(English, Vietnamese);

    ASSERT_EQ("Trường", t->translate_wiki("Field", true));
    ASSERT_EQ("Hàm số", t->translate_wiki("Function", true));
    ASSERT_EQ("Dãy", t->translate_wiki("Sequence", true));
}


TEST_F(TranslatorFixture, FrenchToEnglishwiki) {
    t->set_lang(French, English);

    ASSERT_EQ("Vector space", t->translate_wiki("Espace vectoriel", true));
    ASSERT_EQ("Binomial theorem", t->translate_wiki("Formule du binôme de Newton", true));
    ASSERT_EQ("Binomial theorem", t->translate_wiki("binome de newton", true));
    ASSERT_EQ("Field", t->translate_wiki("Corps", true));
}

TEST_F(TranslatorFixture, VietnameseToFrenchWiki) {
    t->set_lang(Vietnamese, French);

    ASSERT_EQ("Suite", t->translate_wiki("Dãy", true));
    ASSERT_EQ("Suite", t->translate_wiki("Dãy số", true));
    ASSERT_EQ("Corps commutatif", t->translate_wiki("Trường", true));
    ASSERT_EQ("Fonction", t->translate_wiki("Hàm số", true));
}


TEST_F(TranslatorFixture, EnglishToJapaenseWiki) {
    t->set_lang(English, Japanese);

    ASSERT_EQ("列", t->translate_wiki("Sequence", true));
}
