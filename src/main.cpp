#include <iostream>
#include <vector>
#include "CommandManager.h"
#include "FileUtils.h"
#include "MarkdownConverter.h"
#include "MarkdownCreator.h"

using namespace std;

int main(int argc, char const *argv[])
{
  CommandManager commandManager;
  MarkdownCreator markdownCreator;
  MarkdownConverter markdownConverter;

  commandManager.addCommand("help",
                            {}, "Show all commands\nExample: help\nTips:\n - Use {{ NEW_PAGE }} in the template to jump to a new page\n - This bold strings will be replaced by an icon in the HTML: WARNING, INFO, TIP, NOTE, ERROR, SUCCESS",
                            [&commandManager](const std::vector<string> &params)
                            { commandManager.showHelp(); });

  commandManager.addCommand("create",
                            {{"filepath", "Path to the file to create"},
                             {"-wt | -withoutTemplate", "Flag to create without template (true/false)"}},
                            "Create a markdown file with the specified parameters\nExample: create ./report -wt",
                            [&markdownCreator](const vector<string> &params)
                            { markdownCreator.create(params); });

  commandManager.addCommand("convert",
                            {{"filepath", "Path to the file to convert"}},
                            "Convert a markdown file to HTML\nExample: convert ./report.md",
                            [&markdownConverter](const vector<string> &params)
                            { markdownConverter.convert(params); });

  if (argc > 1)
  {
    commandManager.executeCommand(argv[1], {argv + 2, argv + argc});
  }
  else
  {
    commandManager.showHelp();
  }
  return 0;
}
