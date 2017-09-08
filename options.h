#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>
#include <unordered_map>

// Handles a string,string key/value store
// case-insensitive options

// TODO: Give each option a shown string value and an integer value
// TODO: be able to 'increment' options through a enum?
class Options {
 public:
  // returns empty string if option not found
  std::string GetOption(std::string option);

  void SetOption(std::string option, std::string value);
 private:
  std::unordered_map<std::string, std::string> options_;
};

#endif