#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <yaml.h>

class Config
{
  public:
    typedef YAML::Node Node;
    Config(std::istream &input) throw();
    const Node &operator[](const std::string &key) const;

  protected:
    Node _doc;
};

#endif // _CONFIG_H_
