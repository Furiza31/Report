#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "MarkdownCreator.h"
#include "FileUtils.h"
#include "Config.h"

using namespace std;

void MarkdownCreator::create(const vector<string> &params)
{
  string filepath = "./report.md";
  bool withTemplate = true;

  if (params.size() > 2)
  {
    cout << "Invalid number of parameters" << endl;
    return;
  }

  for (const auto &param : params)
  {
    if (param == "-wt" || param == "-withoutTemplate")
    {
      withTemplate = false;
    }
    else
    {
      filepath = param;
      // check if the last 3 characters are ".md"
      if (param.size() < 3 || param.substr(param.size() - 3) != ".md")
      {
        filepath += ".md";
      }
    }
  }
  MarkdownCreator::createFile(filepath, withTemplate);
}

void MarkdownCreator::createFile(const string &filepath, bool withTemplate)
{
  FileUtils fileUtils;
  cout << "Creating file " << filepath
       << (withTemplate ? " with " : " without ")
       << "template..." << endl;

  try
  {
    if (withTemplate)
    {
      string MarkdownTemplate = fileUtils.readFile(MARKDOWN_TEMPLATE_PATH);
      fileUtils.replaceStringInFile(MarkdownTemplate, HTML_DATE, MarkdownCreator::getCurrentDate());
      fileUtils.writeFile(filepath, MarkdownTemplate);
    }
    else
    {
      fileUtils.writeFile(filepath, "");
    }
    cout << "File created successfully!" << endl;
  }
  catch (const std::exception &e)
  {
    cerr << "Error: " << e.what() << endl;
  }
}

string MarkdownCreator::getCurrentDate()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  char dateStr[20];
  strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", ltm);
  return dateStr;
}