#include "options.h"

#include <algorithm>

int Options::GetOptionValue(std::string option) {
  std::transform(option.begin(), option.end(), option.begin(), ::tolower);
  if (options_.find(option) == options_.end()) {
    // value not found in map
    return -1;
  } else {
    return options_[option].second;    
  }
}

std::string Options::GetOptionText(std::string option) {
  std::transform(option.begin(), option.end(), option.begin(), ::tolower);
  if (options_.find(option) == options_.end()) {
    // value not found in map
    return "";
  } else {
    return options_[option].first;    
  }
}

// set the option using the integer value
void SetOption(std::string option, int value) {

}

void Options::SetOption(std::string option, std::string value) {
  std::transform(option.begin(), option.end(), option.begin(), ::tolower);
  std::transform(value.begin(), value.end(), value.begin(), ::tolower);

  if (option == "difficulty") {
    DifficultyOption diff_option = DifficultyValueFromString(value);
    if (diff_option == DifficultyOption::TOTAL_NUM_DIFFICULTY) {
      printf("Error: difficulty option %s is not valid!\n", value.c_str());
    }
  }
  
  options_[option] = std::make_pair(value, 0);
}

// CONVERTERS

DifficultyOption Options::DifficultyValueFromString(std::string value) {
  if (value == "easy") {
    return DifficultyOption::EASY;
  } else if (value == "medium") {
    return DifficultyOption::MEDIUM;
  } else if (value == "hard") {
    return DifficultyOption::HARD;
  } else {
    return DifficultyOption::TOTAL_NUM_DIFFICULTY;
  }
}
std::string Options::DifficultyStringFromValue(DifficultyOption value) {
  if (value == DifficultyOption::EASY) {
    return "easy";
  } else if (value == DifficultyOption::MEDIUM) {
    return "medium";
  } else if (value == DifficultyOption::HARD) {
    return "hard";
  } else {
    return "";
  }
}