#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>
#include <utility>
#include <unordered_map>

enum class DifficultyOption {
  EASY = 0,
  MEDIUM,
  HARD,
  TOTAL_NUM_DIFFICULTY
};

// Handles a string,string key/value store
// case-insensitive options

// TODO: Give each option a shown string value and an integer value
// TODO: be able to 'increment' options through a enum?
class Options {
 public:
  // returns -1 if option not found
  int GetOptionValue(std::string option);

  // returns empty string if option not found
  std::string GetOptionText(std::string option);

  // set the option just by the descriptor
  void SetOption(std::string option, std::string value);

  // set the option using the integer value
  void SetOption(std::string option, int value);
 private:
  // An option is a string key corresponding to a string value and and integer value
  std::unordered_map<std::string, std::pair<std::string, int>> options_;

  DifficultyOption DifficultyValueFromString(std::string value);
  std::string DifficultyStringFromValue(DifficultyOption value);
};

#endif