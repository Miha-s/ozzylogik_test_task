#include "words_counter.hpp"

#include <list>
#include <unordered_set>

class UniqueWordsSequenceCounter {
  std::unordered_set<std::string_view> m_words_in_sequence;
  std::list<std::string_view> m_longest_words_sequence;
  std::list<std::string_view> m_words_sequence;

public:
  void add_word(const std::string_view &word) {
    if (m_words_in_sequence.count(word) > 0) {
      handle_collision(word);
    }

    m_words_sequence.push_back(word);
    m_words_in_sequence.insert(word);
  }

  const std::list<std::string_view> get_longest_words_sequence() {
    if (m_words_sequence.size() > m_longest_words_sequence.size()) {
      return m_words_sequence;
    }

    return m_longest_words_sequence;
  }

private:
  void handle_collision(const std::string_view &word) {
    if (m_words_sequence.size() > m_longest_words_sequence.size()) {
      m_longest_words_sequence = m_words_sequence;
    }

    bool found = false;
    for (auto it = m_words_sequence.begin();;) {
      if (*it == word)
        found = true;
      m_words_in_sequence.erase(*it);
      m_words_sequence.erase(it++);

      if (found) {
        break;
      }
    }
  }
};

WordsCounter::WordsCounter(const std::string &text) : m_text(std::move(text)) {}

void WordsCounter::process() {
  bool prev_alpha = false;
  size_t prev_alpha_start = 0;
  size_t words_count = 0;
  auto view = std::string_view(m_text);
  std::unordered_set<std::string_view> unique_strings;
  UniqueWordsSequenceCounter sequence_counter;

  auto process_new_word = [&](const std::string_view &word) {
    unique_strings.insert(word);
    words_count++;
    sequence_counter.add_word(word);
  };

  for (int i = 0; i < view.size(); i++) {
    if (std::isalpha(m_text[i]) && !prev_alpha) {
      prev_alpha_start = i;
      prev_alpha = true;
    }

    if (!std::isalpha(m_text[i]) && prev_alpha) {
      if (m_text[i] == '\'' && i + 1 < view.size()) {
        if (std::isalpha(m_text[i + 1])) {
          continue;
        }
      }

      auto word = view.substr(prev_alpha_start, i - prev_alpha_start);
      process_new_word(word);
      prev_alpha = false;
    }
  }

  if (prev_alpha) {
    auto word = view.substr(prev_alpha_start);
    process_new_word(word);
  }

  const auto &longest_sequence = sequence_counter.get_longest_words_sequence();

  m_result =
      Result{words_count, unique_strings.size(), longest_sequence.size()};
}

const WordsCounter::Result &WordsCounter::get_result() { return m_result; }
