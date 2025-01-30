#ifndef WORDS_COUNTER_HPP
#define WORDS_COUNTER_HPP
#include <string>

class WordsCounter {
public:
    struct Result {
        size_t words_count;
        size_t unique_words_count;
        size_t longest_unique_words_sequence_count;
    };

    WordsCounter(const std::string &text);

    void process();

    const Result &get_result();

  private:
    std::string_view m_text;
    Result m_result;
};

#endif
