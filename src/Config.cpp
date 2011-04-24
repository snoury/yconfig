#include "Config.h"

namespace
{
  inline const Config::Node &getsub(const std::string &key, const Config::Node &doc)
  {
    const std::size_t pos = key.find_first_of("/");
    return pos == std::string::npos ?
             doc[key] : getsub(key.substr(pos+1, key.length()), doc[key.substr(0, pos)]);
  }
}

Config::Config(std::istream &input) throw()
{
  YAML::Parser(input).GetNextDocument(_doc);
}

const Config::Node &Config::operator[](const std::string &key) const
{
  return getsub(key, _doc);
}
