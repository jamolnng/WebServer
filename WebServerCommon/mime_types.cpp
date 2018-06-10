#include "mime_types.h"

#include <fstream>
#include <vector>
#include "string_utils.h"

using webserver::utils::MimeTypes;
using webserver::utils::STLUtils;
using webserver::utils::StringUtils;

MimeTypes::MimeTypes(const std::filesystem::path& path) { load(path); }

void MimeTypes::load(const std::filesystem::path& path) {
  std::ifstream in(path, std::ios::binary);
  std::string line;
  while (std::getline(in, line)) {
    std::vector<std::string> splitType = StringUtils::split(line, ' ', 2);
    if (splitType.size() == 2) {
      std::string type = splitType[0];
      std::vector<std::string> splitExt = StringUtils::split(splitType[1], ' ');
      for (auto& s : splitExt) items[s] = type;
    }
  }
}

const STLUtils::ci_map<std::string, std::string>& MimeTypes::operator*() const {
  return items;
}

std::string& MimeTypes::operator[](const std::string& item) {
  return items.insert(std::make_pair(item, std::string())).first->second;
}

std::string& MimeTypes::operator[](std::string&& item) {
  return items.try_emplace(std::move(item)).first->second;
}

void MimeTypes::clear() { items.clear(); }

bool MimeTypes::has(const std::string& item) {
  return items.find(item) != items.end();
}
