#include <fstream>
#include <stdexcept>
#include <iostream>
#include "FileUtils.h"

using std::string;

string FileUtils::readFile(const string &filePath)
{
  string content;
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not open file " + filePath);
  }
  string line;
  while (std::getline(file, line))
  {
    content += line + "\n";
  }
  file.close();
  return content;
}

void FileUtils::writeFile(const string &filePath, const string &content)
{
  std::ofstream file(filePath);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not write to file " + filePath);
  }
  file << content;
  file.close();
}

void FileUtils::replaceStringInFile(std::string &str, const std::string &from, const std::string &to)
{
  size_t startPos = 0;

  // Find all occurrences of 'from' and replace with 'to'
  while ((startPos = str.find(from, startPos)) != std::string::npos)
  {
    str.replace(startPos, from.length(), to);
    startPos += to.length(); // Move past the replaced substring
  }
}