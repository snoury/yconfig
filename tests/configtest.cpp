#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Config.h>

#define assert(COND) if(!(COND)) { std::cerr << "Assertion failed (line " << __LINE__ \
                                             <<"): " << #COND << std::endl; exit(-1); }

struct float4 { float x, y, z, w; };
struct Player { std::string name; unsigned int life; float4 position; };

void operator>>(const Config::Node &n, float4 &f4)
{
  assert(n.GetTag() == "!float4"); // optional type-check
  n[0] >> f4.x; n[1] >> f4.y; n[2] >> f4.z; n[3] >> f4.w;
}

void operator>>(const Config::Node &n, Player &p)
{
  assert(n.GetTag() == "!Player"); // optional type-check
  n["name"] >> p.name;
  n["life"] >> p.life;
  n["position"] >> p.position;
}

std::ostream &operator<<(std::ostream &s, const float4 &f4)
{
  s << "(" << f4.x << ", " << f4.y << ", " << f4.z << ", " << f4.w << ")";
}

std::ostream &operator<<(std::ostream &s, const Player &p)
{
  return s << "<Player: name=" << p.name << ", life=" << p.life << ", position=" << p.position << ">";
}

int main(int argc, char **argv)
{
  std::cout << "#### Test case 1 ####" << std::endl;
  {
    std::ifstream f("test/configtest1.yaml");
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
    std::ifstream f("test/configtest2.yaml");
    Config cfg(f);

    std::vector<Player> players = cfg["players"];

    for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
      std::cout << *it << std::endl;      
  }
  std::cout << std::endl << std::endl;
  
  std::cout << "#### Test case 3 ####" << std::endl;
  {
    std::ifstream f("test/configtest3.yaml");
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
