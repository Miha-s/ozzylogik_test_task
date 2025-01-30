#include "json_convertor.hpp"
#include <boost/json.hpp>

namespace json = boost::json;

std::string convert_to_json(const WordsCounter::Result &result) {

  json::object obj;
  obj["words_count"] = result.words_count;
  obj["unique_words_count"] = result.unique_words_count;
  obj["longest_unique_words_sequence"] = result.unique_words_count;

  return json::serialize(obj);
}
