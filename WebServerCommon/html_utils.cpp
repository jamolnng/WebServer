#include "html_utils.h"

void webserver::utils::HTMLUtils::xmlEscape(std::string& data) {
  std::string buf;
  buf.reserve(static_cast<size_t>(std::floor(buf.size() * 1.1)));
  for (auto& c : data) {
    switch (c) {
      case '&':
        buf.append("&amp;");
        break;
      case '\"':
        buf.append("&quot;");
        break;
      case '\'':
        buf.append("&apos;");
        break;
      case '<':
        buf.append("&lt;");
        break;
      case '>':
        buf.append("&gt;");
        break;
      default:
        buf += c;
        break;
    }
  }
  data.swap(buf);
}
