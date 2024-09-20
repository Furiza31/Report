#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <filesystem>
#include "MarkdownCreator.h"
#include "FileUtils.h"
#include "Config.h"

using namespace std;
namespace fs = std::filesystem;

void MarkdownCreator::create(const vector<string> &params)
{
  fs::path filepath = "report.md";
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
      if (filepath.extension() != ".md")
      {
        filepath += ".md";
      }
    }
  }
  MarkdownCreator::createFile(filepath.string(), withTemplate);
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
      cout << "Checking template file." << endl;

      string programDirectory = fileUtils.getProgramDirectory();

      fs::path markdownTemplatePath = fs::path(programDirectory) / MARKDOWN_TEMPLATE_PATH;

      string markdownTemplate = fileUtils.readFile(markdownTemplatePath.string());
      cout << "Read template successfully." << endl;

      fileUtils.replaceStringInFile(markdownTemplate, HTML_DATE, MarkdownCreator::getCurrentDate());

      fileUtils.writeFile(filepath, markdownTemplate);
    }
    else
    {
      cout << "Creating file without template." << endl;
      fileUtils.writeFile(filepath, "");
    }
    cout << "File created successfully!" << endl;
  }
  catch (const std::exception &e)
  {
    cerr << "Error: " << e.what() << endl;
  }
}

std::string MarkdownCreator::getCurrentDate()
{
  cout << "Getting current date..." << endl;
  time_t now = time(0);
  tm *ltm = localtime(&now);
  char dateStr[20];
  strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", ltm);
  return std::string(dateStr);
}
