#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Config.h>

#define assert(COND) if(!(COND)) { std::cerr << "Assertion failed (line " << __LINE__ \
                                             <<"): " << #COND << std::endl; exit(-1); }

struct float3 { float x, y, z; };
struct Player { std::string name; unsigned int life; float3 position; };

void operator>>(const Config::Node &n, float3 &f3)
{
  assert(n.GetTag() == "!float3"); // optional type-check
  n[0] >> f3.x; n[1] >> f3.y; n[2] >> f3.z;
}

void operator>>(const Config::Node &n, Player &p)
{
  assert(n.GetTag() == "!Player"); // optional type-check
  n["name"] >> p.name;
  n["life"] >> p.life;
  n["position"] >> p.position;
}

std::ostream &operator<<(std::ostream &s, const float3 &f3)
{
  s << "(" << f3.x << ", " << f3.y << ", " << f3.z << ")";
}

std::ostream &operator<<(std::ostream &s, const Player &p)
{
  return s << "<Player: name=" << p.name << ", life=" << p.life << ", position=" << p.position << ">";
}

int main(int argc, char **argv)
{
  std::cout << "#### Test case 1 ####" << std::endl;
  {
    std::ifstream f("tests/configtest1.yaml");
    Config cfg(f);

    unsigned int width = cfg["screen/width"];
    unsigned int height = cfg["screen/height"];
    std::map<std::string, double> consts = cfg["constants"];

    std::cout << "screen/width = " << width << std::endl;
    std::cout << "screen/height = " << height << std::endl;
    std::cout << "constants/..." << std::endl;

    for(std::map<std::string, double>::iterator it = consts.begin(); it != consts.end(); ++it)
      std::cout << " ... " << it->first << " = " << it->second << std::endl;
  }
  std::cout << std::endl << std::endl;

  std::cout << "#### Test case 2 ####" << std::endl;
  {
    std::ifstream f("tests/configtest2.yaml");
    Config cfg(f);

    std::vector<Player> players = cfg["players"];

    for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
      std::cout << *it << std::endl;      
  }
  std::cout << std::endl << std::endl;
  
  std::cout << "#### Test case 3 ####" << std::endl;
  {
    std::ifstream f("tests/configtest3.yaml");
    Config cfg(f);
    
    const Config::Node &techniques = cfg["techniques"];

    for(int t = 0; t < techniques.size(); ++t)
    {
      const std::string name = techniques[t]["name"];
      const Config::Node &passes = techniques[t]["passes"];

      std::cout << "Technique " << name << ":" << std::endl;

      for(int p = 0; p < passes.size(); ++p)
      {
        const std::string vs = passes[p]["vertex_shader"];
        const std::string fs = passes[p]["fragment_shader"];
        
        std::cout << "  Pass #" << p << ":" << std::endl;
        std::cout << "    Vertex shader: " << vs << std::endl;
        std::cout << "    Fragment shader: " << fs << std::endl;
      }
    }
  }

  return 0;
}
