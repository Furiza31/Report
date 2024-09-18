#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>

using std::string;

class FileUtils
{
public:
  string readFile(const string &filePath);
  void writeFile(const string &filePath, const string &content);
  string getCurrentWorkingDirectory();
  static void replaceStringInFile(string &str, const string &from, const string &to);
};

#endif