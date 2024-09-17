#ifndef MARKDOWN_CONVERTER_H
#define MARKDOWN_CONVERTER_H

#include <iostream>
#include <vector>

using namespace std;

class MarkdownConverter
{
private:
    string convertToHtml(const string &markdown);
    void replaceTagsToIcons(string &html);

public:
    void convert(const vector<string> &params);
};

#endif