#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

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
  while ((startPos = str.find(from, startPos)) != std::string::npos)
  {
    str.replace(startPos, from.length(), to);
    startPos += to.length();
  }
}

string FileUtils::getProgramDirectory()
{
  char path[PATH_MAX];

#ifdef _WIN32
  if (GetModuleFileName(NULL, path, MAX_PATH) == 0)
  {
    throw std::runtime_error("Could not determine program directory");
  }
  std::string fullPath(path);
  std::size_t pos = fullPath.find_last_of("\\/");
  return fullPath.substr(0, pos);

#elif __linux__
  ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
  if (count == -1)
  {
    throw std::runtime_error("Could not determine program directory");
  }
  std::string fullPath(path, (count > 0) ? count : 0);
  std::size_t pos = fullPath.find_last_of("/");
  return fullPath.substr(0, pos);
#else
  throw std::runtime_error("Unsupported platform");
#endif
}
