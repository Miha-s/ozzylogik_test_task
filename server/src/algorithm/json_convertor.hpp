#ifndef JSON_CONVERTOR_HPP
#define JSON_CONVERTOR_HPP
#include "words_counter.hpp"
#include <string>

std::string convert_to_json(const WordsCounter::Result &result);

#endif // JSON_CONVERTOR_HPP
