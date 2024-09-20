#ifndef MARKDOWNCREATOR_H
#define MARKDOWNCREATOR_H

#include <iostream>
#include <vector>

using namespace std;

class MarkdownCreator
{
private:
  void createFile(const string &filepath, bool withTemplate);
  string getCurrentDate();

public:
  void create(const vector<string> &params);
};

#endif
