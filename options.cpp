#include "options.h"

#include <algorithm>

std::string Options::GetOption(std::string option) {
  std::transform(option.begin(), option.end(), option.begin(), ::tolower);
  return options_[option];
}

void Options::SetOption(std::string option, std::string value) {
  std::transform(option.begin(), option.end(), option.begin(), ::tolower);
  std::transform(value.begin(), value.end(), value.begin(), ::tolower);  
  options_[option] = value;
}