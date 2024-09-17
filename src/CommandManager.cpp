#include "CommandManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

void CommandManager::addCommand(const string &commandName, const vector<Parameter> &commandParameters,
                                const string &commandDescription,
                                const function<void(const vector<string> &)> &commandFunction)
{
  Command cmd = {commandName, commandParameters, commandDescription, commandFunction};
  commands.push_back(cmd);
}

void CommandManager::showHelp() const
{
  cout << endl;
  cout << "Available commands: " << endl;
  for (const auto &cmd : commands)
  {
    cout << "Command: " << cmd.name << endl;
    cout << "Description: " << cmd.description << endl;
    if (!cmd.parameters.empty())
    {
      cout << "Parameters: " << endl;
      for (const auto &param : cmd.parameters)
      {
        cout << "   " << param.name << " - " << param.description << endl;
      }
    }
    cout << endl;
  }
}

void CommandManager::executeCommand(const string &commandName, const vector<string> &commandParameters) const
{
  auto it = find_if(commands.begin(), commands.end(),
                    [&commandName](const Command &cmd)
                    {
                      return cmd.name == commandName;
                    });

  if (it != commands.end())
  {
    it->execute(commandParameters);
  }
  else
  {
    cout << "Command not found!" << endl;
    CommandManager::showHelp();
  }
}
