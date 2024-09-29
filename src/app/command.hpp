
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <initializer_list>
#include <string>
#include <vector>

/*
*****************************
  DO NOT MODIFY THIS FILE
*****************************
*/

class Command {
 private:
  std::string name_;
  int num_args_;
  std::string message_;
  std::vector<std::string> option_prompts_;

  static std::initializer_list<Command> commands;

 public:
  static const Command HELP;
  static const Command EXIT;
  static const Command INVALID;

  static const Command ADD_DATA;
  static const Command CLEAR_DATA;
  static const Command SHOW_DATA;
  static const Command TRAIN_CLASSIFIER;
  static const Command SHOW_CLASSIFIER;
  static const Command CLASSIFY;

  Command(const std::string &name, int num_args, const std::string &message);
  Command(const std::string &name, int num_args, const std::string &message,
          const std::vector<std::string> &option_prompts);

  std::string GetName() const;
  bool HasArguments() const;
  int GetNumArgs() const;
  bool HasOptions() const;
  int GetNumOptions() const;
  std::string GetMessage() const;
  std::string GetOptionPrompt(int index) const;

  bool operator==(const Command &other) const;
  bool operator!=(const Command &other) const;

  static std::string GetHelp();
  static bool IsValidCommand(const std::string &cmd_input);
  static const Command &Find(const std::string &cmd_input);
};

#endif  // COMMAND_HPP
