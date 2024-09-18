#ifndef CONFIG_H
#define CONFIG_H
#include <filesystem>

// define a constant for the template path
#define MARKDOWN_TEMPLATE_PATH std::filesystem::path("templates/default.md").string()
#define HTML_TEMPLATE_PATH std::filesystem::path("templates/default.html").string()
#define HTML_WARNING_ICON "<div class='icon'>⚠️</div>"
#define HTML_WARNING_TAG "<strong>WARNING</strong>"
#define HTML_TIP_ICON "<div class='icon'>💡</div>"
#define HTML_TIP_TAG "<strong>TIP</strong>"
#define HTML_ERROR_ICON "<div class='icon'>❌</div>"
#define HTML_ERROR_TAG "<strong>ERROR</strong>"
#define HTML_SUCCESS_ICON "<div class='icon'>✅</div>"
#define HTML_SUCCESS_TAG "<strong>SUCCESS</strong>"
#define HTML_INFO_ICON "<div class='icon'>💭</div>"
#define HTML_INFO_TAG "<strong>INFO</strong>"
#define HTML_NOTE_ICON "<div class='icon'>📝</div>"
#define HTML_NOTE_TAG "<strong>NOTE</strong>"
#define HTML_NEW_PAGE "{{ NEW_PAGE }}"
#define HTML_NEW_PAGE_REPLACEMENT "<div class='new_page'></div>"
#define HTML_DATE "{{ DATE }}"

#endif