#include <iostream>
#include <vector>
#include "MarkdownConverter.h"
#include "cmark-gfm.h"
#include "cmark-gfm-core-extensions.h"
#include "FileUtils.h"
#include "Config.h"

using namespace std;

void MarkdownConverter::convert(const vector<string> &params)
{
  FileUtils fileUtils;
  string htmlFileName;
  if (params.size() != 1)
  {
    cerr << "Invalid number of parameters\n";
    return;
  }
  if (params[0].size() < 3 || params[0].substr(params[0].size() - 3) != ".md")
  {
    throw std::runtime_error("Invalid file extension. Please provide a markdown file with a .md extension");
  }
  else
  {
    htmlFileName = params[0].substr(0, params[0].size() - 3) + ".html";
  }
  try
  {
    string markdown = fileUtils.readFile(params[0]);
    string HTMLTemplate = fileUtils.readFile(HTML_TEMPLATE_PATH);
    string html = convertToHtml(markdown);
    fileUtils.replaceStringInFile(HTMLTemplate, "<!-- MARKDOWN_CONTENT -->", html);
    replaceTagsToIcons(HTMLTemplate);
    fileUtils.writeFile(htmlFileName, HTMLTemplate);
    cout << "Conversion of " << params[0] << " to " << htmlFileName << " completed successfully\n";
  }
  catch (const std::runtime_error &e)
  {
    cerr << e.what() << endl;
    return;
  }
}

string MarkdownConverter::convertToHtml(const string &markdown)
{
  cmark_gfm_core_extensions_ensure_registered();

  cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);

  cmark_syntax_extension *table_extension = cmark_find_syntax_extension("table");
  cmark_syntax_extension *tasklist_extension = cmark_find_syntax_extension("tasklist");

  if (table_extension)
    cmark_parser_attach_syntax_extension(parser, table_extension);

  if (tasklist_extension)
    cmark_parser_attach_syntax_extension(parser, tasklist_extension);

  cmark_parser_feed(parser, markdown.c_str(), markdown.length());

  cmark_node *document = cmark_parser_finish(parser);
  char *html = cmark_render_html(document, CMARK_OPT_DEFAULT, NULL);
  cmark_node_free(document);
  cmark_parser_free(parser);

  string result(html);
  free(html);

  return result;
}

void MarkdownConverter::replaceTagsToIcons(string &html)
{
  FileUtils fileUtils;
  fileUtils.replaceStringInFile(html, HTML_WARNING_TAG, HTML_WARNING_ICON);
  fileUtils.replaceStringInFile(html, HTML_INFO_TAG, HTML_INFO_ICON);
  fileUtils.replaceStringInFile(html, HTML_TIP_TAG, HTML_TIP_ICON);
  fileUtils.replaceStringInFile(html, HTML_NOTE_TAG, HTML_NOTE_ICON);
  fileUtils.replaceStringInFile(html, HTML_ERROR_TAG, HTML_ERROR_ICON);
  fileUtils.replaceStringInFile(html, HTML_SUCCESS_TAG, HTML_SUCCESS_ICON);
  fileUtils.replaceStringInFile(html, HTML_NEW_PAGE, HTML_NEW_PAGE_REPLACEMENT);
}