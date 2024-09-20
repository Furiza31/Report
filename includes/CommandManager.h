#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>

#ifdef _WIN32
// Include Windows-specific headers here if needed
#include <windows.h>
#elif defined(__linux__)
// Include Linux-specific headers here if needed
#include <unistd.h>
#endif

using std::string;

class CommandManager
{
public:
  struct Parameter
  {
    string name;
    string description;
  };
  struct Command
  {
    string name;
    std::vector<Parameter> parameters;
    string description;
    std::function<void(const std::vector<string> &)> execute;
  };
  void addCommand(const string &commandName, const std::vector<Parameter> &commandParameters,
                  const string &commandDescription,
                  const std::function<void(const std::vector<string> &)> &commandFunction);
  void showHelp() const;
  void executeCommand(const string &commandName, const std::vector<string> &commandParameters) const;

private:
  std::vector<Command> commands;
};

#endif
